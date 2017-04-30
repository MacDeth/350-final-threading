/*
  James D'Angelo
    800112091
    jmdangelo@mix.wvu.edu
  Taylor Miller
    800112547
    tamiller1@mix.wvu.edu
*/
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include "queue.h"
#include <pthread.h>

typedef struct ThreadPool {
  int worker_count;
  int active; /* boolean */
  Queue* queue;
  pthread_t* workers;
  pthread_attr_t joinable;
} ThreadPool;

ThreadPool* CreateThreadPool(int count);
void DestroyThreadPool(ThreadPool* thread_pool);
void EnqueueJob(ThreadPool* thread_pool, Job* job);
void ExecuteJobs(ThreadPool* thread_pool);
int IsThreadPoolActive(ThreadPool* thread_pool); /* boolean */
int GetNumberOfRemainingJobs(ThreadPool* thread_pool);
void* Worker(void* args);

#endif /* end of include guard: THREAD_POOL_H_ */
