#include "worker.h"
#include "dispatcher.h"
#include <chrono>

using namespace std;

// --- GET CONDITION ---
void Worker::getCondition(condition_variable* &cv) {
	cv = &(this)->cv;
}

// --- GET MUTEX ---
void Worker::getMutex(mutex* &mtx) {
    mtx = &(this)->mtx;
}

// --- RUN ---
// Runs the worker instance.
void Worker::run() {
    while (running) {
          if (ready) {
                ready = false;
                frame->process();
                frame->finish();
          }
                      if (Dispatcher::addWorker(this)) {
                while (!ready && running) {
                      //unique_lock<mutex> ulock(mtx);
                      if (cv.wait_for(ulock, chrono::seconds(1)) == cv_status::timeout) {
                      }
                }
          }
    }
 } 
