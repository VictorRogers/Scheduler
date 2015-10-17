#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>

struct Job {
  char jobName[3];
  unsigned int arrivalTime;
  unsigned int serviceTime;
  unsigned int priorityLevel;
};

void init();
void runScheduler();

#endif
