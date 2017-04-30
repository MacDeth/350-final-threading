/*
  James D'Angelo
    800112091
    jmdangelo@mix.wvu.edu
  Taylor Miller
    800112547
    tamiller1@mix.wvu.edu
*/

#include <pthread.h>
#include "thread_pool.h"
#include "queue.h"
#include "job.h"
#include <stdio.h>
#include <stdlib.h>
ThreadPool* CreateThreadPool(int count)
{
	if(count <= 0) return NULL;

	ThreadPool* thread_pool = (ThreadPool*) malloc(sizeof(ThreadPool)); //create pool
	thread_pool->queue = CreateQueue(); //create queue
	thread_pool->active = FALSE; //inactive
	thread_pool->workers = (pthread_t*) malloc(count * sizeof(pthread_t)); //create threads
	thread_pool->worker_count = count; //set count
	return thread_pool;
}

void DestroyThreadPool(ThreadPool* thread_pool)
{
	if(thread_pool == NULL) return;

	DestroyQueue(thread_pool->queue); //destroy the queue
	free(thread_pool->workers); //free the workers
	pthread_attr_destroy(&thread_pool->joinable); //destroy the attribute
	thread_pool->workers = NULL; //set points to null
	thread_pool->queue = NULL;
	free(thread_pool); //free the pool
}

void EnqueueJob(ThreadPool* thread_pool, Job* job)
{
	if(thread_pool == NULL || job == NULL)
		return;

	Enqueue(thread_pool->queue, job);
}

void ExecuteJobs(ThreadPool* thread_pool)
{
	if(thread_pool == NULL || thread_pool->queue->size <= 0)
		return;

	pthread_attr_init(&thread_pool->joinable); //init the attributes
	pthread_attr_setdetachstate(&thread_pool->joinable, PTHREAD_CREATE_JOINABLE);

	int i;
	for(i = 0; i < thread_pool->worker_count; i++)
	{
		//create a worker thread
		if(pthread_create(&thread_pool->workers[i], &thread_pool->joinable, &Worker, thread_pool))
					return;
	}
	thread_pool->active = TRUE; //set active
}

int IsThreadPoolActive(ThreadPool* thread_pool)
{
	if(thread_pool == NULL)
			return FALSE;
	return thread_pool->active;
}

int GetNumberOfRemainingJobs(ThreadPool* thread_pool)
{
	if(thread_pool == NULL || thread_pool->queue->size <= 0)
			return 0;

	return GetQueueSize(thread_pool->queue);
}

void* Worker(void* args)
{
	if(args == NULL)
	{
		return NULL;
	}

	ThreadPool* thread_pool = (ThreadPool*) args;

	Job* temp;
	while(GetNumberOfRemainingJobs(thread_pool) > 0) //loop until all jobs have been executed
	{
		temp = Dequeue(thread_pool->queue); //take out of queue
		if(temp != NULL)
		{
			(temp->job_description)(temp->input, temp->output); //run the process
		}
		free(temp); //free the job
	}
	thread_pool->active = FALSE; //deactivate queue
	pthread_exit(NULL);
}
