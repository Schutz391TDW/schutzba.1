//Andrew Schutzbach
//CS 4760
//Project 1
//09/03/2021
//Source: Robbins/Robbins

#include <string.h>
#include <errno.h>
#include "log.h"

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

//Adding messages to log
int addmsg(char type, const char * msg){
	
	//New node
	log_t *newLog;
	
    	//Allocate memory
    	newLog = malloc(sizeof(log_t));

    	if (newLog == NULL) {
        	//For unsuccessful log
        	printf("driver:ERROR in log %s\n", strerror(errno));
        	return -1;
    	}
    
	
	//For setting up time for formating
    	time_t epoch_seconds;
    	epoch_seconds = time(NULL);
    	newLog->item.hours = ((epoch_seconds / 3600) % 24) - 5;
    	newLog->item.minutes = ((epoch_seconds / 60) % 60);
    	newLog->item.seconds = (epoch_seconds % 60);
    	newLog->item.timeChar = malloc(10*sizeof(char) + 1);

    	//Setting time as HH:MM:SS for log.
    	sprintf( newLog->item.timeChar, "[%02u:%02u:%02u]", newLog->item.hours, newLog->item.minutes, newLog->item.seconds);

    	newLog->item.type = type;
    	newLog->item.string = malloc(strlen(msg) + 1);
    	strcpy(newLog->item.string, msg);

    	if (headptr == NULL) {
        	//Attachs head node
        	headptr = newLog;
        	//Attachs tail node
        	tailptr = newLog;
    	} else {
        	//For attaching tail
        	tailptr->next = newLog;
        	//Attachs tail node
        	tailptr = newLog;
    	}
	//Successful
    	return 0;
}

//Clears log and memory
void clearlog(){

	while(headptr != NULL ){
        	log_t *ptr = headptr->next;
        	free(headptr);
        	headptr = ptr;
    	}
}

//Allocates space and makes log into string
char *getlog(){

	char *fullLog;
    	char *dataToAdd;
    	log_t *nodePtr = headptr;
    	int memoryReq = 0;
    	int count = 0;

    	while (nodePtr != NULL){
        	memoryReq = strlen(nodePtr->item.timeChar) + sizeof(nodePtr->item.type) + strlen(nodePtr->item.string)+1;
        	count += memoryReq;
        	nodePtr = nodePtr->next;
    	}
    	//Reset nodePtr to head
    	nodePtr = headptr;
    	if((fullLog = (char*)malloc(count)) == NULL) {
        	printf("driver: ERROR with memmory. %s\n", strerror(errno));
        	return NULL;
    	}
    	if ((dataToAdd = (char*)malloc(64))== NULL) {
        	printf("driver: ERROR with memmory. %s\n", strerror(errno));
        	return NULL;
    	}
    	while(nodePtr != NULL) {
        	memoryReq = strlen(nodePtr->item.timeChar) + sizeof(nodePtr->item.type) + strlen(nodePtr->item.string)+1;
        	if((dataToAdd = (char*)realloc(dataToAdd, memoryReq)) == NULL){
            	printf("driver: ERROR with memmory. %s\n", strerror(errno));
            	return NULL;
        	}
        	sprintf(dataToAdd, "%s %c: %s\n", nodePtr->item.timeChar, nodePtr->item.type, nodePtr->item.string);
        	strcat(fullLog, dataToAdd);
        	nodePtr = nodePtr->next;
    	}

    	//Free up memmory 
    	free(dataToAdd);
    	return fullLog;
}

//Saving log
int savelog(char *fileName){

	FILE *save;
    	save = fopen(fileName, "w");

	//Error check before saving
    	if (save == NULL) {
        	perror("ERROR can't save");
        	return -1;
    	} else {
        	//Start writing to file
        	log_t *nodePtr = headptr;
        	while(nodePtr != NULL ){
			fprintf( save, "%s %c: %s\n", nodePtr->item.timeChar, nodePtr->item.type, nodePtr->item.string);
            		nodePtr = nodePtr->next;
        	}
        	//Close file or exits if unable to close
        	if(fclose(save) == -1) {
			perror("ERROR: can't close");
            		exit(EXIT_FAILURE);
        	} else {
            		return 0;
        	}
    	}
}
