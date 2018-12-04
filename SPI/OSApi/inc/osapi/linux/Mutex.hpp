#ifndef OSAPI_LINUX_MUTEX_HPP
#define OSAPI_LINUX_MUTEX_HPP
#include <pthread.h>
#include <iostream>

namespace osapi
{
  class Mutex
  {
  public:
    Mutex();
    void lock();
    void unlock();
    ~Mutex();
    pthread_mutex_t mut;
  
  };
}


#endif
