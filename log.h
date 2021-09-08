//Andrew Schutzbach
//CS 4760
//Project 1
//09/03/2021
//Source: Robbins/Robbins

#include <time.h>

typedef struct data_struct
{
	time_t time;
	char type;
	char* string;
} data_t;

int addmsg(const char type, const char* msg);
void clearlog();
char* getlog();
int savelog(char* filename);
