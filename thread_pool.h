/*
  James D'Angelo
    800112091
    jmdangelo@mix.wvu.edu
  Taylor Miller
    555555555
    example@mix.wvu.edu
*/

#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

typedef struct ThreadPool {
  int worker_count;
  int active; /* boolean */
  Queue* queue;
  pthread_t* workers;
  void joinable; /* TODO: what type for this?? */
} ThreadPool;

ThreadPool* CreateThreadPool(int count);
void DestroyThreadPool();
void EnqueueJob(ThreadPool* thread_pool, Job* job);
void ExecuteJobs(ThreadPool* thread_pool);
int IsThreadPoolActive(ThreadPool* thread_pool); /* boolean */
int GetNumberOfRemainingJobs(ThreadPool* thread_pool);

#endif /* end of include guard: THREAD_POOL_H_ */
