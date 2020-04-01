#include "dispatcher.h"
#include <iostream>

using namespace std;

// Static initialisations.
queue<AbstractFrame*> Dispatcher::frames;
queue<Worker*> Dispatcher::workers;
mutex Dispatcher::framesMutex;
mutex Dispatcher::workersMutex;
vector<Worker*> Dispatcher::allWorkers;
vector<thread*> Dispatcher::threads;

// --- INIT ---
// Start the number of requested worker threads.
bool Dispatcher::init(int workers) {
	thread* t = 0;
	Worker* w = 0;

	for (int i = 0; i < workers; ++i) {
		w = new Worker;
		allWorkers.push_back(w);
		t = new thread(&Worker::run, w);
		threads.push_back(t);
	}
	
	return true;
}

// --- STOP ---
// Terminate the worker threads and clean up.
bool Dispatcher::stop() {
    for (int i = 0; i < allWorkers.size(); ++i) {
          allWorkers[i]->stop();
    }
          cout << "Stopped workers.\n";
          for (int j = 0; j < threads.size(); ++j) {
          threads[j]->join();
                      cout << "Joined threads.\n";
    }

    return true;
} 

// --- ADD FRAME ---
void Dispatcher::addFrame(AbstractFrame* frame) {
    workersMutex.lock();

    if (!workers.empty()) {
          Worker* worker = workers.front();
          worker->setFrame(frame);
          condition_variable* cv;
          //mutex* mtx;
          worker->getCondition(cv);
          //worker->getMutex(mtx);
          //unique_lock<mutex> lock(*mtx);
          cv->notify_one();
          workers.pop();
          workersMutex.unlock();
    }
    else {
          workersMutex.unlock();
          framesMutex.lock();
          frames.push(frame);
          framesMutex.unlock();
    }
} 

// --- ADD WORKER ---
bool Dispatcher::addWorker(Worker* worker) {
    bool wait = true;
    framesMutex.lock();

    if (!frames.empty()) {
          AbstractFrame* frame = frames.front();
          worker->setFrame(frame);
          frames.pop();
          wait = false;
          framesMutex.unlock();
    }
    else {
          framesMutex.unlock();
          workersMutex.lock();
          workers.push(worker);
          workersMutex.unlock();
    }
          return wait;
} 
