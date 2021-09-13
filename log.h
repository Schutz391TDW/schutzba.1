//Andrew Schutzbach
//CS 4760
//Project 1
//09/03/2021
//Source: Robbins/Robbins

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef LOG_H
#define LOG_H

typedef struct data_struct
{
	time_t time;
	int hours;
	int minutes;
    	int seconds;
    	char *timeChar;
    	char type;         
    	char *string;  
} data_t;

int addmsg(char type, const char * msg);
void clearlog();
char* getlog();
int savelog(char * fileName);

#endif
