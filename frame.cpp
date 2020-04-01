#include "frame.h"


// --- PROCESS ---
void Frame::process() {
	outFnc("Starting processing frame " + std::to_string(value) + "...");

	//
}


// --- FINISH ---
void Frame::finish() {
	outFnc("Finished frame " + std::to_string(value));
}
