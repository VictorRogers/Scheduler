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
  struct Job *nextJob;
};

void enqueueJob(struct Job *job, struct Job **firstJob, struct Job **lastJob);
struct Job * dequeueJob(struct Job **firstJob, struct Job **lastJob);

unsigned int isJobComplete(struct Job *cpuJob);
void init();
void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs);

#endif
