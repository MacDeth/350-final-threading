/*
  James D'Angelo
    800112091
    jmdangelo@mix.wvu.edu
  Taylor Miller
    555555555
    example@mix.wvu.edu
*/

#include <stdlib.h>
#include <stdio.h> /* DELETE THIS LINE LATER AND ALL DEBUG PRINTS */
#include "queue.h"
#include "job.h"

/* I made a fucking stack instead of a queue because I'm retarded. */

Queue* CreateQueue() {
  Queue* temp = (Queue*) malloc(sizeof(Queue));

  temp->first = NULL;
  temp->size = 0;

  return temp;
}

void DestroyQueue(Queue* queue) {
  if (!queue) return;
  Job* current = queue->first;
  Job* temp = NULL;

  do {
    temp = current;
    current = current->next;
    free(temp);
  } while(current->next);

  free(current);
  free(queue);
}

void Enqueue(Queue* queue, Job* job) {
  if (!queue || !job) return;

  job->next = queue->first;
  queue->first = job;

  queue->size++;
}

Job* Dequeue(Queue* queue) {
  if (!queue) return NULL;
  Job* last = queue->first;
  Job* prev = NULL;

  if (last) {
    while (last->next) {
      prev = last;
      last = last->next;
    }

    prev->next = NULL;
    queue->size--;
  }

  return last;
}

int GetQueueSize(Queue* queue) {
  if (!queue) return 0;
  return queue->size;
}
