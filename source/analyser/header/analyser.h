#ifndef ANALYSER_H
#define ANALYSER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Job {
	char jobName[3];
	unsigned int arrivalTime;
	unsigned int waitTime;
	unsigned int completeTime;
};

void init();

void analysePerformance(struct Job fcfsJobs[100], struct Job hpfJobs[100], struct Job rrJobs[100],
		                    struct Job sjfJobs[100], unsigned int fcfsNumberOfJobs,
												unsigned int hpfNumberOfJobs, unsigned int rrNumberOfJobs,
												unsigned int sjfNumberOfJobs);

#endif
