#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Job {
  char jobName[3];
  unsigned int arrivalTime;
  unsigned int serviceTime;
  unsigned int priorityLevel;
  struct Job *nextJob;
};

struct Job *firstJob;
struct Job *lastJob;

void enqueueJob(struct Job *job);
void dequeueJob();
void printJobQueue();

void init();
void runScheduler(struct Job jobs[100], unsigned int numberOfJobs);

#endif
