#pragma once
#ifndef WORKER_H
#define WORKER_H

#include "abstract_frame.h"
#include <condition_variable>
#include <mutex>

using namespace std;

class Worker {
	condition_variable cv;
	mutex mtx;
	unique_lock<mutex> ulock;
	AbstractFrame* frame;
	bool running;
	bool ready;
	
public:
	Worker() { running = true; ready = false; ulock = unique_lock<mutex>(mtx); }
	void run();
	void stop() { running = false; }
	void setFrame(AbstractFrame* frame) { this->frame = frame; ready = true; }
	void getCondition(condition_variable* &cv);
    void getMutex(mutex* &mtx);
};

#endif
