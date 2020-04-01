#pragma once
#ifndef ABSTRACT_FRAME_H
#define ABSTRACT_FRAME_H

class AbstractFrame {
	//
	
public:
	virtual void setValue(int value) = 0;
	virtual void process() = 0;
	virtual void finish() = 0;
};

#endif
