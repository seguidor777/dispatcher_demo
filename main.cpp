#include "dispatcher.h"
#include "frame.h"
#include <iostream>
#include <string>
#include <csignal>
#include <thread>
#include <chrono>

using namespace std;

// Constants
const int MAX_THREADS = thread::hardware_concurrency();

// Globals
sig_atomic_t signal_caught = 0;
mutex logMutex;

void sigint_handler(int sig) {
	signal_caught = 1;
}

void logFnc(string text) {
	logMutex.lock();
	cout << text << endl;
	logMutex.unlock();
}

int main() {
	// Install signal handler.
	signal(SIGINT, &sigint_handler);

    cout << "Concurrent threads supported: " << MAX_THREADS << endl;

	// Initialise the dispatcher with 10 worker threads.
	Dispatcher::init(MAX_THREADS);
	
	cout << "Initialised." << endl;
	
	// Generate frames in a continuous loop until terminated with SIGINT
    int cycles = 0;
	Frame* frame = 0;

	while (!signal_caught) {
		frame = new Frame();
		frame->setValue(cycles);
		frame->setOutput(&logFnc);
		Dispatcher::addFrame(frame);// FIXME
        cout << "Cycles=" << cycles << endl;
		cycles++;
	}

	// Cleanup.
	Dispatcher::stop(); // FIXME
	cout << "Clean-up done." << endl;

	return 0;
}
