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

#endif
