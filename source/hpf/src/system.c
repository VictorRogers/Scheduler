#include "system.h"
#include "fcfs.h"

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

  start(&cpu, jobs, numberOfJobs);

  fclose(ifp); 
}

unsigned int isJobComplete(unsigned int serviceTime) {
  if (serviceTime == 0) {
    return 1;
  }
  else
    return 0;
}

void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs) {

  for (cpu->clockTime; cpu->clockTime < cpu->runTime; cpu->clockTime++) {
    //Need to check for completion of job
    if (cpu->status == 1) {
      printf("-CPU Status-\nClock Time:%u\nCurrent Job: %s\nService Time: %u\n\n",
             cpu->clockTime, firstJob->jobName, firstJob->serviceTime);
      //firstJob->serviceTime--;
    }
    //Time Quantum

    //Arrival Queue
    for (unsigned int i = 0; i < numberOfJobs; i++) {
      //arrivalFCFS(cpu, jobs, i);
    }

    //Run Scheduler
    //scheduleFCFS(cpu);
  }
}

void enqueueJob(struct Job *job) {
  struct Job *tempJob = (struct Job*)malloc(sizeof(struct Job));

  strcpy(tempJob->jobName, job->jobName);
  tempJob->arrivalTime = job->arrivalTime;
  tempJob->serviceTime = job->serviceTime;
  tempJob->priorityLevel = job->priorityLevel;
  tempJob->nextJob = NULL;

  if (firstJob == NULL && lastJob == NULL) {
    firstJob = lastJob = tempJob;
    return;
  }

  lastJob->nextJob = tempJob;
  lastJob = tempJob;
}

void dequeueJob() {
  struct Job *tempJob = firstJob;

  if (firstJob == NULL) {
    printf("Job queue is empty\n");
    return;
  }

  if (firstJob == lastJob) {
    firstJob = lastJob = NULL;
  }
  else {
    firstJob = firstJob->nextJob;
  }

  free(tempJob);
}


void printJobQueue() {
  struct Job *tempJob = firstJob;

  while (tempJob != NULL) {
    printf("%s %u %u %u\n", tempJob->jobName, tempJob->arrivalTime,
                            tempJob->serviceTime, tempJob->priorityLevel);
    tempJob = tempJob->nextJob;
  }
}


void heapInsert(struct Job job, struct Job *jobHeap, int size) {
  int i;
  struct Job tempJob;
  i = size + 1;
  jobHeap[i] = job;
  while (jobHeap[i].priorityLevel > jobHeap[i/2].priorityLevel && i > 1) {
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
    if (child < size) {
      if (jobHeap[child].priorityLevel < jobHeap[child + 1].priorityLevel) {
        child++;
      }
    }
    if (jobHeap[child].priorityLevel > jobHeap[i].priorityLevel) {
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
  //int child;
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

void enqueuePriority(struct Job job, struct PriorityQueue *pq) {
  heapInsert(job, pq->jobHeap, pq->size);
  pq->size++;
}

struct Job dequeuePriority(struct PriorityQueue *pq) {
  struct Job removedJob = heapRemove(pq->jobHeap, pq->size);
  pq->size--;
  return removedJob;
}

void initPriorityQueue(struct PriorityQueue *pq, int size) {
  pq->size = 0;
  pq->jobHeap = (struct Job*)malloc(sizeof(struct Job)*(size+1));  
}
