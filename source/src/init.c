#include "init.h"

void init() {
  FILE *ifp;
  char *ifMode = "r";
  struct Job jobs[100];
  unsigned int i = 0;
  unsigned int numberOfJobs;

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

  runScheduler(jobs, numberOfJobs);

  fclose(ifp); 
}

unsigned int isJobComplete(unsigned int serviceTime) {
  if (serviceTime == 0) {
    return 1;
  }
  else
    return 0;
}

void runScheduler(struct Job jobs[100], unsigned int numberOfJobs) {
  unsigned int clockTime = 0;
  unsigned int runTime = 1000;
  unsigned int cpuStatus = 0;
  unsigned int currentJob = 0;

  for (clockTime; clockTime < runTime; clockTime++) {
    for (unsigned int i = 0; i < numberOfJobs; i++) {
      if (jobs[i].arrivalTime == clockTime) {
        enqueueJob(&jobs[i]);
      }
    }
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

