#ifndef CHAT_BASE_THREADPOOL
#define CHAT_BASE_THREADPOOL


#include "Mutex.h"
#include "Condition.h"

#include <stdint.h>
#include <queue>
#include <functional>

namespace chat {
    namespace base {
        // using Task = void(*)()
        using Task = std::function<void()>;
        class ThreadPool {
        public:
            ThreadPool(uint32_t threadNums):
            threadNums_(threadNums), mutex_(), notFull_(mutex_), notEmpty_(mutex_){
                
            }
            // push a task into queue
            void run(Task task);
            // take a task from queue
            Task take();
            // start loop
            void start();
            void threadFunc();
        private:
            bool full(){
                return taskQueue_.size() == maxQueueSize_; 
            }
            uint32_t threadNums_;
            std::queue<Task> taskQueue_;
            uint32_t maxQueueSize_;
            Mutex mutex_;
            Condition notFull_, notEmpty_;
        };
    }
}

#endif