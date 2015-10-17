#include "init.h"

void init() {
  FILE *ifp;
  char *ifMode = "r";
  struct Job jobs[100];
  unsigned int i = 0;
  unsigned int numberOfJobs;

  ifp = fopen("../input/input.txt", ifMode);

  if (ifp == NULL) {
    perror("Error");
    exit(1);
  }
  
  while (!feof(ifp)) {
    fscanf(ifp, "%s %u %u %u\n", jobs[i].jobName, &jobs[i].arrivalTime,
                             &jobs[i].serviceTime, &jobs[i].priorityLevel);
    i++;
    numberOfJobs = i;
  }

  runScheduler(jobs);

  fclose(ifp); 
}

void runScheduler(struct Job jobs[100]) {

  printf("%s", jobs[0].jobName);
}
