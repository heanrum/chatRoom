#ifndef CHAT_BASE_MUTEX
#define CHAT_BASE_MUTEX

#include <pthread.h>

namespace chat{
    namespace base{

        class Mutex{
        public:
            Mutex(){
                pthread_mutex_init(&mutex_, NULL);
            }
            ~Mutex(){
                pthread_mutex_destroy(&mutex_);
            }
            void lock(){
                pthread_mutex_lock(&mutex_);
            }
            void unlock(){
                pthread_mutex_unlock(&mutex_);
            }
            pthread_mutex_t* get_mutex(){
                return &mutex_;
            }
        private:
            pthread_mutex_t mutex_;
        };

        class MutexLock{
        public:
            MutexLock(const Mutex& mutex):mutex_(mutex){
                mutex_.lock();
            }
            ~MutexLock(){
                mutex_.unlock();
            }
        private:
            Mutex mutex_;
        };

    }
}


#endif