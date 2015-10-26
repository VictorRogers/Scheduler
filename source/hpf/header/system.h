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
  struct Job *nextJob;
};

struct PriorityQueue {
  struct Job *jobHeap;
  int size;
};

struct Job *firstJob;
struct Job *lastJob;

void enqueueJob(struct Job *job);
void dequeueJob();
void printJobQueue();

void init();
void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs);

void heapInsert(struct Job job, struct Job *jobHeap, int size);
void downHeap(struct Job *jobHeap, int size, int i);
struct Job heapRemove(struct Job *jobHeap, int size);
void buildHeap(struct Job *jobHeap, int size);

void enqueuePriority(struct Job job, struct PriorityQueue *pq);
struct Job dequeuePriority(struct PriorityQueue *pq);
void initPriorityQueue(struct PriorityQueue *pq, int size);

#endif
