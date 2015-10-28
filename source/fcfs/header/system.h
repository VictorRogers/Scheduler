#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Victor Rogers
 * CS 420
 * First Come First Serve Scheduler Simulation
 *
 * FCFS Declarations and Structs
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

//enqueueJob - Adds a job to the rear of the wait queue
//           - Param 1 - Pointer to the job to be inserted into the wait queue
//           - Param 2 - Double pointer to the first job in the queue
//           - Param 3 - Double pointer to the last job in the queue
void enqueueJob(struct Job *job, struct Job **firstJob, struct Job **lastJob);

//dequeueJob - Removes and returns the job at the front of the queue
//           - Param 1 - Double pointer to the first job in the queue
//           - Param 2 - Double pointer to the last job in the queue
struct Job * dequeueJob(struct Job **firstJob, struct Job **lastJob);

//isJobComplete - Checks to see if the current job is complete
//              - Param 1 - Pointer to the current job running in the CPU
unsigned int isJobComplete(struct Job *cpuJob);

//init - Reads in input file containing information on jobs and stores the job information in an array
//              - Inits all of the CPU's information and starts the system
void init();

//start - Starts the CPU and the scheduler. Runs jobs, checks for completion, checks for new arrivals, and dispatches jobs
//      - Once jobs have completed, required information is written to output.txt in the output directory
//      - Param 1 - Pointer to the CPU struct
//      - Param 2 - Jobs array which all jobs are stored in once read in from the input file
//      - Param 3 - Number of jobs read in from the input file
void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs);

#endif
