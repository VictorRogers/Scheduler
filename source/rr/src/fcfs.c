#include "fcfs.h"

void arrivalFCFS(struct CPU *cpu, struct Job jobs[100], unsigned int jobIndex) {
  if (jobs[jobIndex].arrivalTime == cpu->clockTime) {
    enqueueJob(&jobs[jobIndex]);
    if (cpu->status == 0) {
      cpu->status = 1;
    }
  }
}

void scheduleFCFS(struct CPU *cpu) {
  if (cpu->status == 1) {
    if (firstJob->serviceTime == 0) {
      printf("%s Complete\n\n", firstJob->jobName);
      dequeueJob(); 
      if (firstJob == NULL) {
        cpu->status = 0;
      }
    }
  }
}
