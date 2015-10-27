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

struct SJFQueue {
  struct Job *jobHeap;
  int size;
};

void init();
void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs);
unsigned int isJobComplete(struct Job *cpuJob);

void heapInsert(struct Job job, struct Job *jobHeap, int size);
void downHeap(struct Job *jobHeap, int size, int i);
struct Job heapRemove(struct Job *jobHeap, int size);
void buildHeap(struct Job *jobHeap, int size);

void enqueueSJF(struct Job job, struct SJFQueue *sjfQ);
struct Job *dequeueSJF(struct SJFQueue *sjfQ);
void initSJFQueue(struct SJFQueue *sjfQ, int size);

void debug(struct CPU *cpu, struct Job *cpuJob);
#endif
