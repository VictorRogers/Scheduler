#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct CPU {
  unsigned int clockTime;
  unsigned int runTime;
  unsigned int status;
};

struct Job {
  char jobName[3];
  unsigned int arrivalTime;
  unsigned int serviceTime;
  unsigned int priorityLevel;
  unsigned int waitTime;
  unsigned int completeTime;
  unsigned int timeQuantum;
  struct Job *nextJob;
};


void init();
void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs);

unsigned int isJobComplete(struct Job *cpuJob);
unsigned int isTimeQuantumComplete(struct Job *cpuJob);

void enqueueJob(struct Job *job, struct Job **firstJob, struct Job **lastJob);
struct Job * dequeueJob(struct Job **firstJob, struct Job **lastJob);

#endif
