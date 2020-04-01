#pragma once
#ifndef FRAME_H
#define FRAME_H

#include "abstract_frame.h"
#include <string>

using namespace std;

typedef void (*logFunction)(string text);

class Frame : public AbstractFrame {
	int value;
	logFunction outFnc;

public:
	void setValue(int value) { this->value = value; }
	void setOutput(logFunction fnc) { outFnc = fnc; }
	void process();
	void finish();
};

#endif
