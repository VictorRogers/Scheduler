#ifndef FCFS_H
#define FCFS_H

#include "system.h"

void arrivalFCFS(struct CPU *cpu, struct Job jobs[100], unsigned int jobIndex);
void scheduleFCFS(struct CPU *cpu);

#endif
