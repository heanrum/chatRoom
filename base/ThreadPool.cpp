#include "ThreadPool.h"

using namespace std::placeholders;
using namespace chat::base;

using PthreadArgsFunc = void *(*)(void*);

void ThreadPool::threadFunc(){
    while( true ){
        Task task = take();
        task();
    }
}

void * interThreadFunc(void * args){
    ThreadPool* threadPoolPtr = static_cast<ThreadPool*>(args);
    threadPoolPtr->threadFunc();
}

void ThreadPool::start(){
    pthread_t tid;
    // 没有考虑释放pthread
    for(int i=0; i<threadNums_ ; ++i){
        pthread_create(&tid, NULL, interThreadFunc, static_cast<void*>(this));
    }
}

void ThreadPool::run(Task task){
    MutexLock lock(mutex_);
    while( full() ){
        notFull_.wait();
    }
    if( !full() ){
        taskQueue_.push(task);
        notEmpty_.notify();
    }
}

Task ThreadPool::take(){
    MutexLock lock(mutex_);
    while( taskQueue_.empty() ){
        notEmpty_.wait();
    }
    // may return empty object
    Task task;
    if( !taskQueue_.empty() ){
        task = taskQueue_.front();
        taskQueue_.pop();
        if( taskQueue_.size() == maxQueueSize_ - 1 ){
            notFull_.notify();
        }
    }
    return task;
}