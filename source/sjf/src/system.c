#include "system.h"

void init() {
  FILE *ifp;
  char *ifMode = "r";
  struct Job jobs[100];
  unsigned int i = 0;
  unsigned int numberOfJobs;
  
  struct CPU cpu; 
  cpu.clockTime = 0;
  cpu.runTime = 1000;
  cpu.status = 0;

  ifp = fopen("input/input.txt", ifMode);

  if (ifp == NULL) {
    perror("Error opening input file");
    exit(1);
  }
  
  while (!feof(ifp)) {
    fscanf(ifp, "%s %u %u %u\n", jobs[i].jobName, &jobs[i].arrivalTime,
                             &jobs[i].serviceTime, &jobs[i].priorityLevel);
    i++;
    numberOfJobs = i;
  }

  fclose(ifp); 
  start(&cpu, jobs, numberOfJobs);
}



void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs) {
  FILE *ofp;
  char *ofMode = "w";
  struct Job *cpuJob = NULL;
  struct SJFQueue sjfQ;

  initSJFQueue(&sjfQ, numberOfJobs);

  ofp = fopen("output/output.txt", ofMode);

  if (ofp == NULL) {
    perror("Error creating output file");
    exit(1);
  }

  
  //Check for completion
  for (cpu->clockTime = 0; cpu->clockTime < cpu->runTime; cpu->clockTime++) {
    if (cpu->status == 1) {
      if (isJobComplete(cpuJob)) {
        cpu->status = 0;
        cpuJob->completeTime = cpu->clockTime;
        fprintf(ofp, "%s %u %u %u\n", cpuJob->jobName, cpuJob->arrivalTime,
                                      cpuJob->waitTime, cpuJob->completeTime);
        free(cpuJob);
        cpuJob = NULL;
      }
    }

    //Check for arrivals
    for (unsigned int i = 0; i < numberOfJobs; i++) {
      if (jobs[i].arrivalTime == cpu->clockTime) {
        enqueueSJF(jobs[i], &sjfQ);
      }
    }

    //Dispatch
    if (cpu->status == 0) {
      if (sjfQ.size > 0) {
        cpuJob = dequeueSJF(&sjfQ);
        cpuJob->waitTime = cpu->clockTime - cpuJob->arrivalTime;
        cpu->status = 1;
      }
    }

    if (cpu->status == 1) {
      cpuJob->serviceTime--;
    }
  }
  free(cpuJob);
  fclose(ofp); 
}


unsigned int isJobComplete(struct Job *cpuJob) {
  if (cpuJob->serviceTime == 0) {
    return 1;
  }
  else {
    return 0;
  }
}


void heapInsert(struct Job job, struct Job *jobHeap, int size) {
  int i;
  struct Job tempJob;
  i = size + 1;
  jobHeap[i] = job;
  while (jobHeap[i].serviceTime < jobHeap[i/2].serviceTime && i > 1) {
    tempJob = jobHeap[i];
    jobHeap[i] = jobHeap[i/2];
    jobHeap[i/2] = tempJob;
    i = i/2;
  }
}


void downHeap(struct Job *jobHeap, int size, int i) {
  int child;
  struct Job tempJob;
  unsigned int downHeap = 1;
  while (downHeap) {
    child = i*2;
    if (child > size) {
      downHeap = 0;
    }
    else if (child < size) {
      if (jobHeap[child].serviceTime > jobHeap[child + 1].serviceTime) {
        child++;
      }
    }
    else if (jobHeap[child].serviceTime < jobHeap[i].serviceTime) {
      tempJob = jobHeap[child];
      jobHeap[child] = jobHeap[i];
      jobHeap[i] = tempJob;
      i = child;
    }
    else {
      downHeap = 0;
    }
  }
}


struct Job heapRemove(struct Job *jobHeap, int size) {
  struct Job removedJob = jobHeap[1];
  jobHeap[1] = jobHeap[size];
  size--;
  downHeap(jobHeap, size, 1);
  return removedJob;
}


void buildHeap(struct Job *jobHeap, int size) {
  int i;
  for (i = size/2; i > 0; i--) {
    downHeap(jobHeap, size, i);
  }
}


void enqueueSJF(struct Job job, struct SJFQueue *sjfQ) {
  heapInsert(job, sjfQ->jobHeap, sjfQ->size);
  sjfQ->size++;
}


struct Job * dequeueSJF(struct SJFQueue *sjfQ) {
  struct Job *returnJob = (struct Job*)malloc(sizeof(struct Job));
  struct Job removedJob = heapRemove(sjfQ->jobHeap, sjfQ->size);
  *returnJob = removedJob;
  
  sjfQ->size--;
  return returnJob;
}


void initSJFQueue(struct SJFQueue *sjfQ, int size) {
  sjfQ->size = 0;
  sjfQ->jobHeap = (struct Job*)malloc(sizeof(struct Job)*(size+1));  
}

void debug(struct CPU *cpu, struct Job *cpuJob) {
  printf(" -DEBUG-\n");
  printf("Clock Time: %u\n", cpu->clockTime);
  printf("CPU Status: %u\n", cpu->status);
  if (cpuJob == NULL) {
    printf("   CPU Job: None\n\n");
  }
  else {
    printf("   CPU Job: %s\n", cpuJob->jobName);
    printf("CPU Job ST: %u\n", cpuJob->serviceTime);
    printf("CPU Job PL: %u\n\n", cpuJob->priorityLevel);
  }
}
