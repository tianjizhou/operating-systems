// =======================================
// Team members:
//
// Jinghua Feng 	fengj3	
// Jihui Nie		niej
// Tianji Zhou		zhout2
//
// github link: https://github.com/tianjizhou/operating-system/
// =======================================

// FILE: io.h
#ifndef _io_h
#define _io_h

#include <list>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "clock.h"
#include "ready_queue.h"

// It is assumed that no content switching time required for writing into IO or ready queue. 
class IO {

	public:

		// CONSTRUCTOR
		IO();

		// ACCESSOR
		std::string PIDs();
		bool empty() const { return processes_.empty(); }

		// MODIFIER
		void push(Process *p);
		std::vector<Process *> pop();
		void run();


	private:

		// REPRESENTATION
		std::list<Process *> processes_;


};

#endif
