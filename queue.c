/*
  James D'Angelo
    800112091
    jmdangelo@mix.wvu.edu
  Taylor Miller
    800112547
    tamiller1@mix.wvu.edu
*/

#include <stdlib.h>
#include <stdio.h> /* DELETE THIS LINE LATER AND ALL DEBUG PRINTS */
#include "queue.h"
#include "job.h"


Queue* CreateQueue() {
  Queue* temp = (Queue*) malloc(sizeof(Queue));

  temp->first = NULL;
  temp->size = 0;
  pthread_mutex_init(&temp->mutex, NULL);
  return temp;
}

void DestroyQueue(Queue* queue) {
  if (!queue) return;
  Job* temp;

  while(queue->size > 0)
  {
	  temp = Dequeue(queue);
	  free(temp);
  }

  free(queue);
}

void Enqueue(Queue* queue, Job* job) {
  if (!queue || !job) return;
  pthread_mutex_lock(&queue->mutex);
  Job* temp = queue->first;

  if(queue->first == NULL)
  {
	  queue->first = job;
  }
  else
  {
	  while(temp->next != NULL)
		  temp = temp->next;

	  temp->next = job;
  }

  queue->size++;
  pthread_mutex_unlock(&queue->mutex);
}

Job* Dequeue(Queue* queue) {
  if (!queue) return NULL;
  if(queue->first == NULL) return NULL;

  pthread_mutex_lock(&queue->mutex);
  Job* temp = queue->first;
  queue->first = temp->next;
  queue->size--;
  pthread_mutex_unlock(&queue->mutex);

  return temp;
}

int GetQueueSize(Queue* queue) {
  if (!queue) return -1;
  int size;

  pthread_mutex_lock(&queue->mutex);
  size = queue->size;
  pthread_mutex_unlock(&queue->mutex);
  return size;
}
