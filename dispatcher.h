#pragma once
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "abstract_frame.h"
#include "worker.h"
#include <queue>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

class Dispatcher {
	static queue<AbstractFrame*> frames;
	static queue<Worker*> workers;
	static mutex framesMutex;
	static mutex workersMutex;
	static vector<Worker*> allWorkers;
	static vector<thread*> threads;

public:
	static bool init(int workers);
	static bool stop();
	static void addFrame(AbstractFrame* frame);
	static bool addWorker(Worker* worker);
};

#endif
