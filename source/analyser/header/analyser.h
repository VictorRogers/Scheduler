#ifndef ANALYSER_H
#define ANALYSER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Victor Rogers
 * CS 420
 * Statistical Analyser for Scheduling Algorithms 
 *
 * Analyser Declarations and Structs 
 */

struct Job {
	char jobName[3];
	unsigned int arrivalTime;
	unsigned int waitTime;
	unsigned int completeTime;
};


//Reads in data from scheduling algorithm output files and prepares them for statistical analysis
void init();

//Performs computations for mean and variance on all of the algorithm's data sets
void analysePerformance(struct Job fcfsJobs[100], struct Job hpfJobs[100], struct Job rrJobs[100],
		                    struct Job sjfJobs[100], unsigned int fcfsNumberOfJobs,
												unsigned int hpfNumberOfJobs, unsigned int rrNumberOfJobs,
												unsigned int sjfNumberOfJobs);

#endif
