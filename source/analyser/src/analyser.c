#include "analyser.h"

/* Victor Rogers
 * CS 420
 * Statistical Analyser for Scheduling Algorithms 
 *
 * Analyser Implementation
 */

//Reads in data from scheduling algorithm output files and prepares them for statistical analysis
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

//Performs computations for mean and variance on all of the algorithm's data sets
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
	float fcfsVariance = 0;
	float hpfVariance = 0;
	float rrVariance = 0;
	float sjfVariance = 0;

	//First Come First Served Computations
	for (unsigned int i = 0; i < fcfsNumberOfJobs; i++) {
    fcfsWaitSum = fcfsWaitSum + fcfsJobs[i].waitTime;
	}
	fcfsWaitAvg = fcfsWaitSum / fcfsNumberOfJobs;
	for (unsigned int i = 0; i < fcfsNumberOfJobs; i++) {
    fcfsVariance = fcfsVariance + ((fcfsJobs[i].waitTime - fcfsWaitAvg) *
				                           (fcfsJobs[i].waitTime - fcfsWaitAvg));
	}
	fcfsVariance = fcfsVariance / fcfsNumberOfJobs;

  //Highest Priority First Computations
	for (unsigned int i = 0; i < hpfNumberOfJobs; i++) {
    hpfWaitSum = hpfWaitSum + hpfJobs[i].waitTime;
	}
	hpfWaitAvg = hpfWaitSum / hpfNumberOfJobs;
	for (unsigned int i = 0; i < hpfNumberOfJobs; i++) {
    hpfVariance = hpfVariance + ((hpfJobs[i].waitTime - hpfWaitAvg) *
				                           (hpfJobs[i].waitTime - hpfWaitAvg));
	}
	hpfVariance = hpfVariance / hpfNumberOfJobs;
  
	//Round Robin Computations
	for (unsigned int i = 0; i < rrNumberOfJobs; i++) {
    rrWaitSum = rrWaitSum + rrJobs[i].waitTime;
	}
	rrWaitAvg = rrWaitSum / rrNumberOfJobs;
	for (unsigned int i = 0; i < rrNumberOfJobs; i++) {
    rrVariance = rrVariance + ((rrJobs[i].waitTime - rrWaitAvg) *
				                           (rrJobs[i].waitTime - rrWaitAvg));
	}
	rrVariance = rrVariance / rrNumberOfJobs;

  //Shortest Job First Computations
	for (unsigned int i = 0; i < sjfNumberOfJobs; i++) {
    sjfWaitSum = sjfWaitSum + sjfJobs[i].waitTime;
	}
	sjfWaitAvg = sjfWaitSum / sjfNumberOfJobs;
	for (unsigned int i = 0; i < sjfNumberOfJobs; i++) {
    sjfVariance = sjfVariance + ((sjfJobs[i].waitTime - sjfWaitAvg) *
				                           (sjfJobs[i].waitTime - sjfWaitAvg));
	}
	sjfVariance = sjfVariance / sjfNumberOfJobs;

	//Outputting to analysis.txt in the output directory
	fprintf(ofp, "FCFS Wait Average = %d\n", fcfsWaitAvg);
	fprintf(ofp, "FCFS Variance = %f\n\n", fcfsVariance);
	fprintf(ofp, "HPF Wait Average = %d\n", hpfWaitAvg);
	fprintf(ofp, "HPF Variance = %f\n\n", hpfVariance);
	fprintf(ofp, "RR Wait Average = %d\n", rrWaitAvg);
	fprintf(ofp, "RR Variance = %f\n\n", rrVariance);
	fprintf(ofp, "SJF Wait Average = %d\n", sjfWaitAvg);
	fprintf(ofp, "SJF Variance = %f\n\n", sjfVariance);
}
