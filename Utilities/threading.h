#ifndef THREAD_H
#define THREAD_H

#include "Utilities/common.h"

/*!
 * \brief implement a thread with std:thread (c++11 or higher)
 * For using this class and runnig a thread you should define a class inherits this class and reimplement run() function as main thread loop
 */
class Thread {
public:
    Thread() {};
    ~Thread() {};
    /** Returns true if the thread was successfully started, false if there was an error starting the thread */
     bool Start()
     {
         return (pthread_create(&_thread, NULL, _thread_start, this) == 0);
     }
     /** Will not return until the internal thread has exited. */
     void WaitForInternalThreadToExit()
     {
         (void) pthread_join(_thread, NULL);
     }
 protected:
     /** Implement this method in your subclass with the code you want your thread to run. */
     virtual void run() = 0;
 private:
     static void * _thread_start(void * This) {((Thread *)This)->run(); return 0;}
     pthread_t _thread;};

#endif // THREAD_H
