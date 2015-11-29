#include "analyser.h"

void init() {
	FILE *ifp;
	char * ifMode = "r";
	struct Job fcfsJobs[100], Job hpfJobs[100], Job rrJobs[100], Job sjfJobs[100];
	unsigned int fcfsIndex = 0;
	unsigned int fcfsReadComplete = 0;
	unsigned int hpfIndex = 0;
	unsigned int hpfReadComplete = 0;
	unsigned int rrIndex = 0;
	unsigned int rrReadComplete = 0;
	unsigned int sjfIndex = 0;
	unsigned int sjfReadComplete = 0;
	unsigned int fcfsNumberOfJobs, hpfNumberOfJobs, rrNumberOfJobs, sjfNumberOfJobs;
  
	fcfsIFP = fopen("input/fcfsOutput.txt", ifMode);
  hpfIFP = fopen("input/hpfOutput.txt", ifMode);
  rrOFP = fopen("input/rrOutput.txt", ifMode);
	sjfOFP = fopen("input/sjfOutput.txt", ifMode);

	if (fcfsIFP == NULL) {
		perror("Error opening FCFS output file\n");
		exit(1);
	}
	if (hpfIFP == NULL) {
		perror("Error opening HPF output file\n");
		exit(1);
	}
	if (rrOFP == NULL) {
		perror("Error opening RR output file\n");
		exit(1);
	}
	if (sjfOFP == NULL) {
		perror("Error opening SJF output file\n");
		exit(1);
	}

	unsigned int readingFiles = 1;
	while (readingFiles) {
		if (!feof(fcfsIFP)) {
			fscanf(ifp, "%s %u %u %u\n", fcfsJobs[fcfsIndex].jobName, &fcfsJobs[fcfsIndex].arrivalTime,
																	 &fcfsJobs[fcfsIndex].waitTime, &fcfsJobs[fcfsIndex].completeTime);		
			fcfsIndex++;
			fcfsnumberOfJobs = fcfsIndex;
		}
		else {
      fcfsReadComplete = 1;
		}

		if (!feof(fcfsIFP)) {
			fscanf(ifp, "%s %u %u %u\n", fcfsJobs[fcfsIndex].jobName, &fcfsJobs[fcfsIndex].arrivalTime,
																	 &fcfsJobs[fcfsIndex].waitTime, &fcfsJobs[fcfsIndex].completeTime);		
			fcfsIndex++;
			fcfsnumberOfJobs = fcfsIndex;
		}
		else {
      fcfsReadComplete = 1;
	  }

		if (!feof(fcfsIFP)) {
			fscanf(ifp, "%s %u %u %u\n", fcfsJobs[fcfsIndex].jobName, &fcfsJobs[fcfsIndex].arrivalTime,
																	 &fcfsJobs[fcfsIndex].waitTime, &fcfsJobs[fcfsIndex].completeTime);		
			fcfsIndex++;
			fcfsnumberOfJobs = fcfsIndex;
		}
		else {
      fcfsReadComplete = 1;
	  }

		if (!feof(sjfIFP)) {
			fscanf(sjfIFP, "%s %u %u %u\n", fcfsJobs[fcfsIndex].jobName, &fcfsJobs[fcfsIndex].arrivalTime,
																	 &fcfsJobs[fcfsIndex].waitTime, &fcfsJobs[fcfsIndex].completeTime);		
			fcfsIndex++;
			fcfsnumberOfJobs = fcfsIndex;
		}
		else {
      fcfsReadComplete = 1;
	  }

}
