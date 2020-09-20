#ifndef CHAT_BASE_CONDITION
#define CHAT_BASE_CONDITION

#include "Mutex.h"

namespace chat {
    namespace base {

        class Condition{
        public:
            Condition(Mutex& mutex):mutex_(mutex){
                pthread_cond_init(&cond_, NULL);
            }
            void wait(){
                pthread_cond_wait(&cond_, mutex_.get_mutex());
            }
            void notify(){
                pthread_cond_signal(&cond_);
            }
        private:
            Mutex mutex_;
            pthread_cond_t cond_;
        };

    }
}


#endif