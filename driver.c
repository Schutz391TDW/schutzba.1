//Andrew Schutzbach
//CS 4760
//Project 1
//09/04/2021

#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

int main(int argc, char *argv[]){

	int ch = 0;
	int timeN = 1;
	int error, allLog;
    	char *fileName= "message.log";
    	char *message;
	char *fullLog;
    	time_t t;

	//Makes sure log is cleared
	//clearlog();
	
    	while((ch = getopt(argc, argv, "ht:")) != -1){
        	switch(ch){
            		case 'h':
                		//For when -h is called with ./driver. Gives helpful info.
                		printf("Useful info for this program.\n");
                		printf("./driver -h: Is a helper message.\n");
                		printf("./driver -t seconds: Is for printing messages every second, but seconds is randomized by [0, 2*seconds.\n");
                		printf("./driver logfile: Is for changing the file name to where to print\n");
				printf(" ./driver -t seconds logfile: Can also be used. \n");
                		exit(EXIT_SUCCESS);
            		case 't':
				//For when a string is passed for seconds instead of an int
                		if(!isdigit(argv[2][0])) {
                    		printf("%s is not an int! Please run with an int!\n", argv[2]);
                    		exit(EXIT_FAILURE);
                		} else {
					//For when -t is called with ./driver successfully with an int
                    			timeN = atoi(optarg);
                    			//Incase the int passed is neg or 0
                    			if(timeN <= 0){
                        		timeN = 1;
                    			}
                    			break;
                		}
            		default:
				//For default calls
                		printf("Please use program with -h or -t.\n");
                		exit(EXIT_FAILURE);
        	}
    	}
	//For changing file name if one was entered and not starting with int
    	if (argc == 4 || argc == 2) {
        	if (!isdigit(argv[optind][0])) {
            		fileName = argv[optind];
            		strcat(fileName,".log");
        	} else {
			fprintf(stderr, "File name needs to start with a letter.\n");
            		exit(EXIT_FAILURE);
        	}
    	}

    	//For randomizing time
    	int upTime = 0;
	int randNum = (2 * timeN);
	srand((unsigned)time(&t));
	
	allLog = 0;
    	int logCount = 0;
    
	//For starting a loop to add to log
	bool start = true;
	while(start) {
		//Randomizing upTime
        	upTime = rand() % randNum;
        	sleep(upTime);
		
        	//To randomize errors/message type
        	error = rand() % 4;
        
		//Starts adding to logs
        	if (error == 0) {
            		message = "INFO";
            		if (addmsg( 'I', message) == -1) {
                		printf("driver: Unable to add info %s\n", argv[0]);
                		//perror("driver: Unable to add info\n");
            		} else {
                		printf("driver: info added %s\n", argv[0]);
            		}
        	} else if (error == 1) {
            		message = "WARNING";
            		if (addmsg( 'W', message) == -1) {
                		printf("driver: Unable to add warning %s\n", argv[0]);
                		//perror("driver: Unable to add warning\n");
            		} else {
                		printf("driver: warning added %s\n", argv[0]);
            		}
        	} else if(error == 2) {
            		message = "ERROR";
            		if (addmsg( 'E', message) == -1) {
                		printf("driver: Unable to add error %s\n", argv[0]);
                		//perror("driver: Unable to add error\n");
            		} else {
                		printf("driver: error added %s\n", argv[0]);
            		}
        	} else if (error == 3) {
            		message = "FATAL";
            		if (addmsg( 'F', message) == -1) {
                		printf("driver: Unable to add fatal %s\n", argv[0]);
                		//perror("driver: Unable to add fatal");
            		} else {
                		printf("driver: fatal added %s\n", argv[0]);
            		}

            		//Does getLog() for test
            		if ((allLog = getlog()) != NULL) {
                		printf("%s", fullLog);
            		} else {
                		printf("driver: ERROR: unable to get full log %s\n", argv[0]);
                		//perror("driver: ERROR: unable to get full log");
            		}
			if (savelog(fileName) != 0){
                		perror("Unable to save");
            		} else {
                		printf("%s was saved\n", argv[0]);
            		}
            		clearlog();
            		exit(EXIT_SUCCESS);
        	}
		allLog += 1;
        	logCount += 1;
    	}
    	//Does getLog() before cleaned
    	if ((fullLog = getlog()) != NULL){
        	printf("%s", fullLog);
    	} else {
        	//printf("%s: ERROR: unable to get the entire log\n", argv[0]);
        	perror("driver:ERROR: unable to get log");
    	}
	
	//Clears log
    	clearlog();
    	exit(EXIT_SUCCESS);
	return 0;
}
