#include "analyser.h"

void init() {
	FILE *fcfsIFP;
	FILE *hpfIFP;
	FILE *rrIFP;
	FILE *sjfIFP;
	char * ifMode = "r";
	struct Job fcfsJobs[100];
  struct Job hpfJobs[100];
	struct Job rrJobs[100];
	struct Job sjfJobs[100];
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
  rrIFP = fopen("input/rrOutput.txt", ifMode);
	sjfIFP = fopen("input/sjfOutput.txt", ifMode);

	if (fcfsIFP == NULL) {
		perror("Error opening FCFS output file\n");
		exit(1);
	}
	if (hpfIFP == NULL) {
		perror("Error opening HPF output file\n");
		exit(1);
	}
	if (rrIFP == NULL) {
		perror("Error opening RR output file\n");
		exit(1);
	}
	if (sjfIFP == NULL) {
		perror("Error opening SJF output file\n");
		exit(1);
	}

	unsigned int readingFiles = 1;
	while (readingFiles) {
		if (!feof(fcfsIFP)) {
			fscanf(fcfsIFP, "%s %u %u %u\n", fcfsJobs[fcfsIndex].jobName, &fcfsJobs[fcfsIndex].arrivalTime,
																	 &fcfsJobs[fcfsIndex].waitTime, &fcfsJobs[fcfsIndex].completeTime);		
			fcfsIndex++;
			fcfsNumberOfJobs = fcfsIndex;
		}
		else {
      fcfsReadComplete = 1;
		}

		if (!feof(hpfIFP)) {
			fscanf(hpfIFP, "%s %u %u %u\n", hpfJobs[hpfIndex].jobName, &hpfJobs[hpfIndex].arrivalTime,
																	 &hpfJobs[hpfIndex].waitTime, &hpfJobs[hpfIndex].completeTime);		
			hpfIndex++;
			hpfNumberOfJobs = hpfIndex;
		}
		else {
      hpfReadComplete = 1;
	  }

		if (!feof(rrIFP)) {
			fscanf(rrIFP, "%s %u %u %u\n", rrJobs[rrIndex].jobName, &rrJobs[rrIndex].arrivalTime,
																	 &rrJobs[rrIndex].waitTime, &rrJobs[rrIndex].completeTime);		
			rrIndex++;
			rrNumberOfJobs = fcfsIndex;
		}
		else {
      rrReadComplete = 1;
	  }

		if (!feof(sjfIFP)) {
			fscanf(sjfIFP, "%s %u %u %u\n", sjfJobs[sjfIndex].jobName, &sjfJobs[sjfIndex].arrivalTime,
																	 &sjfJobs[sjfIndex].waitTime, &sjfJobs[sjfIndex].completeTime);		
			sjfIndex++;
			sjfNumberOfJobs = sjfIndex;
		}
		else {
      sjfReadComplete = 1;
	  }

		if (fcfsReadComplete && hpfReadComplete && rrReadComplete && sjfReadComplete) {
      readingFiles = 0;
		}
	}
	analysePerformance(fcfsJobs, hpfJobs, rrJobs, sjfJobs, fcfsNumberOfJobs, hpfNumberOfJobs,
			               rrNumberOfJobs, sjfNumberOfJobs);
}

void analysePerformance(struct Job fcfsJobs[100], struct Job hpfJobs[100], struct Job rrJobs[100],
		                    struct Job sjfJobs[100], unsigned int fcfsNumberOfJobs,
												unsigned int hpfNumberOfJobs, unsigned int rrNumberOfJobs,
												unsigned int sjfNumberOfJobs) {
  FILE *ofp;
	char *ofMode = "w";
  
	ofp = fopen("output/analysis.txt", ofMode);

	int fcfsWaitSum = 0;
	int hpfWaitSum = 0;
	int rrWaitSum = 0;
	int sjfWaitSum = 0;
	int fcfsWaitAvg = 0;
	int hpfWaitAvg = 0;
	int rrWaitAvg = 0;
	int sjfWaitAvg = 0;

	for (unsigned int i = 0; i < fcfsNumberOfJobs; i++) {
    fcfsWaitSum = fcfsWaitSum + fcfsJobs[i].waitTime;
	}

	for (unsigned int i = 0; i < hpfNumberOfJobs; i++) {
    hpfWaitSum = hpfWaitSum + hpfJobs[i].waitTime;
	}

	for (unsigned int i = 0; i < rrNumberOfJobs; i++) {
    rrWaitSum = rrWaitSum + rrJobs[i].waitTime;
	}
	
	for (unsigned int i = 0; i < sjfNumberOfJobs; i++) {
    sjfWaitSum = sjfWaitSum + sjfJobs[i].waitTime;
	}
	fcfsWaitAvg = fcfsWaitSum / fcfsNumberOfJobs;
	hpfWaitAvg = hpfWaitSum / hpfNumberOfJobs;
	rrWaitAvg = rrWaitSum / rrNumberOfJobs;
	sjfWaitAvg = sjfWaitSum / sjfNumberOfJobs;
	
	fprintf("FCFS Wait Average = %d\n", fcfsWaitAvg);
	fprintf("HPF Wait Average = %d\n", hpfWaitAvg);
	fprintf("RR Wait Average = %d\n", rrWaitAvg);
	fprintf("SJF Wait Average = %d\n", sjfWaitAvg);
}
