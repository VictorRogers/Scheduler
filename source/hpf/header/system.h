#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* Victor Rogers
 * CS 420
 * Highest Priority First Scheduler Simulation
 *
 * HPF Declarations and Structs
 */
 
//CPU - Stores key information about the simulated CPU
//    Clock time - Current time of the CPU's clock
//    Run Time   - The clock time that the CPU will stop running at
//    Status     - 0 = CPU Idle, 1 = CPU Running
struct CPU {
  unsigned int clockTime;
  unsigned int runTime;
  unsigned int status;
};

//Job - Stores key information about jobs to be run by the simulated CPU
//    Arrival Time   - Time that the job arrived in the wait queue
//    Service Time   - The amount of time that the job needs to run for
//    Priority Level - Priority level of the job - Larger levels means higher priority
//    Wait Time      - Total amount of time that the job has been in the wait queue
//    Complete Time  - The clock time that the job completed at
//    Next Job       - A pointer to the next job in the wait queue
struct Job {
  char jobName[3];
  unsigned int arrivalTime;
  unsigned int serviceTime;
  unsigned int priorityLevel;
  unsigned int waitTime;
  unsigned int completeTime;
  struct Job *nextJob;
};

//Priority Queue - Stores information on the heap that is used to sort jobs by priority
//    Job Heap - Pointer to the heap
//    Size   - Size of the heap
struct PriorityQueue {
  struct Job *jobHeap;
  int size;
};

//init - Reads in input file containing information on jobs and stores the job information in an array
//              - Inits all of the CPU's information and starts the system
void init();

//start - Starts the CPU and the scheduler. Runs jobs, checks for completion, checks for new arrivals, and dispatches jobs
//      - Once jobs have completed, required information is written to output.txt in the output directory
//      - Param 1 - Pointer to the CPU struct
//      - Param 2 - Jobs array which all jobs are stored in once read in from the input file
//      - Param 3 - Number of jobs read in from the input file
void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs);

//isJobComplete - Checks to see if the current job is complete
//              - Param 1 - Pointer to the current job running in the CPU
unsigned int isJobComplete(struct Job *cpuJob);

//heapInsert - Inserts a job into the heap and calls downHeap to sort the job by its priority
//      - Param 1 - The job to be inserted
//      - Param 2 - Pointer to the heap
//      - Param 3 - The size of the heap
void heapInsert(struct Job job, struct Job *jobHeap, int size);

//downHeap - Sorts the heap by job priority
//      - Param 1 - Pointer to the heap
//      - Param 2 - The size of the heap
//		- Param 3 - The location of the job to be sorted in the heap
void downHeap(struct Job *jobHeap, int size, int i);

//heapRemove - Removes a job from the top of the heap
//      - Param 1 - Pointer to the heap
//      - Param 2 - The size of the heap
struct Job heapRemove(struct Job *jobHeap, int size);

//buildHeap - Constructs the heap
//      - Param 1 - Pointer to the heap
//      - Param 2 - The size of the heap
void buildHeap(struct Job *jobHeap, int size);

//enqueuePriority - Enqueues a job into the heap by priority
//      - Param 1 - The job to be inserted
//      - Param 2 - A pointer to the Priority Queue struct
void enqueuePriority(struct Job job, struct PriorityQueue *pq);

//dequeuePriority - Dequeues a job from the top of the heap and returns it
//      - Param 1 - A pointer to the Priority Queue struct
struct Job * dequeuePriority(struct PriorityQueue *pq);

//initPriorityQueue - Initializes the Priority Queue
//      - Param 1 - A pointer to the Priority Queue struct
//		- Param 2 - The size of the Priority Queue
void initPriorityQueue(struct PriorityQueue *pq, int size);

//debug - A function for debugging purposes
//Prints diagnostic information
//		- Param 1 - A pointer to the CPU struct
//		- Param 2 - A pointer to the job currently running in the CPU
void debug(struct CPU *cpu, struct Job *cpuJob);

#endif
