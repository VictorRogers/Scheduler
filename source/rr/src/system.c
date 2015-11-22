#include "system.h"

/* Victor Rogers
 * CS 420
 * Round Robin Scheduler Simulation
 *
 * RR Implementation
 */

//init - Reads in input file containing information on jobs and stores the job information in an array
void init() {
  FILE *ifp;
  char *ifMode = "r";
  struct Job jobs[100];
  unsigned int i = 0;
  unsigned int numberOfJobs;
  
  struct CPU cpu; 
  cpu.clockTime = 0;
  cpu.runTime = 10000;
  cpu.status = 0;

  ifp = fopen("input/input.txt", ifMode);

  if (ifp == NULL) {
    perror("Error opening input file");
    exit(1);
  }
  
  while (!feof(ifp)) {
    fscanf(ifp, "%s %u %u %u\n", jobs[i].jobName, &jobs[i].arrivalTime,
                             &jobs[i].serviceTime, &jobs[i].priorityLevel);
    jobs[i].waitTime = 0;
    jobs[i].timeInCPU = 0;
    i++;
    numberOfJobs = i;
  }

  start(&cpu, jobs, numberOfJobs);

  fclose(ifp); 
}


//start - Starts the CPU and the scheduler. Runs jobs, checks for completion, checks for new arrivals, and dispatches jobs
void start(struct CPU *cpu, struct Job jobs[100], unsigned int numberOfJobs) {
  FILE *ofp;
  char *ofMode = "w";
  unsigned int isQueueEmpty = 1;
  struct Job *cpuJob = NULL;
  struct Job *firstJob = NULL;
  struct Job *lastJob = NULL;

  ofp = fopen("output/rrOutput.txt", ofMode);

  if (ofp == NULL) {
    perror("Error creating output file");
    exit(1);
  }
  
  //Check for completion
  for (cpu->clockTime = 0; cpu->clockTime < cpu->runTime; cpu->clockTime++) {
    if (cpu->status == 1) {
      if (isJobComplete(cpuJob)) {
        cpu->status = 0;
        printf("Name - %s, FST - %u, TICPU - %u\n", cpuJob->jobName, cpuJob->finalStartTime, cpuJob->timeInCPU);
		    cpuJob->waitTime = cpuJob->finalStartTime - cpuJob->timeInCPU - cpuJob->arrivalTime; 
        cpuJob->completeTime = cpu->clockTime;
        fprintf(ofp, "%s %u %u %u\n", cpuJob->jobName, cpuJob->arrivalTime,
                                      cpuJob->waitTime, cpuJob->completeTime);
        free(cpuJob);
        cpuJob = NULL;
      }
      else if (isTimeQuantumComplete(cpuJob)) {
		    cpuJob->timeInCPU = cpuJob->timeInCPU + 10;
        enqueueJob(cpuJob, &firstJob, &lastJob);
        cpu->status = 0;
        free(cpuJob);
        cpuJob = NULL;
      }
    }

    //Check for completion of time quantum

    //Check for arrivals
    for (unsigned int i = 0; i < numberOfJobs; i++) {
      if (jobs[i].arrivalTime == cpu->clockTime) {
        enqueueJob(&jobs[i], &firstJob, &lastJob);
        isQueueEmpty = 0;
      }
    }

    //Dispatch
    if (cpu->status == 0) {
      if (!isQueueEmpty) {
        cpuJob = dequeueJob(&firstJob, &lastJob);
        if (cpuJob == NULL) {
          isQueueEmpty = 1;
          cpu->status = 0;
        }
        else {
          cpuJob->timeQuantum = 10;
          if (cpuJob->serviceTime <= cpuJob->timeQuantum) {
            cpuJob->finalStartTime = cpu->clockTime;
          }
          cpu->status = 1;
        }
      }
    }

    if (cpu->status == 1) {
      cpuJob->serviceTime--;
      cpuJob->timeQuantum--;
    }
  }
  free(cpuJob);
  fclose(ofp); 
}


//isJobComplete - Checks to see if the current job is complete
unsigned int isJobComplete(struct Job *cpuJob) {
  if (cpuJob->serviceTime == 0) {
    return 1;
  }
  else {
    return 0;
  }
}


//isTimeQuantumComplete - Checks to see if the current job's time quantum is complete
unsigned int isTimeQuantumComplete(struct Job *cpuJob) {
  if (cpuJob->timeQuantum == 0) {
    return 1;
  }
  else {
    return 0;
  }
}


//enqueueJob - Adds a job to the rear of the wait queue
void enqueueJob(struct Job *job, struct Job **firstJob, struct Job **lastJob) {
  struct Job *tempJob = (struct Job*)malloc(sizeof(struct Job));

  strcpy(tempJob->jobName, job->jobName);
  tempJob->arrivalTime = job->arrivalTime;
  tempJob->serviceTime = job->serviceTime;
  tempJob->priorityLevel = job->priorityLevel;
  tempJob->waitTime = job->waitTime;
  tempJob->timeInCPU = job->timeInCPU;
  tempJob->completeTime = job->completeTime;
  tempJob->nextJob = NULL;

  if (*firstJob == NULL && *lastJob == NULL) {
    *firstJob = *lastJob = tempJob;
    return;
  }

  (*lastJob)->nextJob = tempJob;
  *lastJob = tempJob;
}


//dequeueJob - Adds a job to the rear of the wait queue
struct Job * dequeueJob(struct Job **firstJob, struct Job **lastJob) {
  struct Job *tempJob = *firstJob;

  if (*firstJob == NULL) {
    return NULL;
  }

  if (*firstJob == *lastJob) {
    *firstJob = *lastJob = NULL;
  }
  else {
    *firstJob = (*firstJob)->nextJob;
  }

  return tempJob;
}
