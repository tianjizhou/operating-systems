// FILE: ready_queue.cpp
#include "ready_queue.h"

// Add new processes into ready queue without sorting
void ReadyQueue::push(std::vector<Process*> new_processes, const std::string& mode, int t, 
                      Clock clk, const std::string & situation) {
	for (unsigned int i = 0; i < new_processes.size(); i++) {
		new_processes[i]->arrive(t);
		processes_.push_back(new_processes[i]);
        clk.PrintTime() ;
        std::cout << "Process " << new_processes[ i ] -> ID() ;
        if ( situation == "arrival" ) 
            std::cout << " arrived and added to ready queue " ;
        else if ( situation == "IO" ) 
            std::cout << " completed I/O; added to ready queue " ;
        else
            std::cout << "Error: Invalid ready_queue push" << std::endl ;
        PrintPIDs() ;
	}
	if (new_processes.size())
		sort(mode);
}

/*
void ReadyQueue::PrintPushProcesses( std::vector<Process*> proc_vec, Clock clk , const std::string & situation ) {
    std::vector<Process*>::iterator itr;
	for (itr = proc_vec.begin(); itr != proc_vec.end(); itr++) {
        clk.PrintTime() ;
        std::cout << "Process " << (*itr) -> ID() ;
        if ( situation == "arrival" ) 
            std::cout << " arrived and added to ready queue " ;
        else if ( situation == "IO" ) 
            std::cout << " completed I/O; added to ready queue " ;
        else
            std::cout << "Error: Invalid ready_queue push" << std::endl ;
        PrintPIDs() ;
	}
}
*/

void ReadyQueue::push(Process* p, const std::string& mode, int t) {
	if (p != NULL) {
		p->arrive(t);
		processes_.push_back(p);
		sort(mode);
	}	
}

Process* ReadyQueue::pop() {
	Process* tmp = processes_.front();
	processes_.pop_front();
	return tmp;
}

// Sort the processes in the ready queue based on different algorithms
void ReadyQueue::sort(const std::string& mode) {
	if (mode == "FCFS")
		processes_.sort(FCFS);
	else if (mode == "SRT")
		processes_.sort(SRT);
	else if (mode == "RR")
		processes_.sort(RR);
	else
		std::cout << "Invalid algorithm" << std::endl;
}

void ReadyQueue::PrintPIDs() {
    std::cout << "[Q" ;
    if( processes_.empty() ) std::cout << " <empty>" ;
    else {
        std::list< Process* > :: iterator it ;
        for ( it = processes_.begin(); it != processes_.end(); ++it )
            std::cout << " " << ( *it ) -> ID() ;
    }
    std::cout << "]" << std::endl ;
}

// Sort algorithms
bool FCFS(Process* p1, Process* p2) {
	return p1->arrival_time() < p2->arrival_time()
		|| (p1->arrival_time() == p2->arrival_time() && p1->ID() < p2->ID());
}

bool SRT(Process* p1, Process* p2) {
	return p1->tCPU() < p2->tCPU()
		|| (p1->tCPU() == p2->tCPU() && p1->ID() < p2->ID());
}

bool RR(Process* p1, Process* p2) {
	return p1->arrival_time() < p2->arrival_time()
		|| (p1->arrival_time() == p2->arrival_time() && p1->ID() < p2->ID());
}
