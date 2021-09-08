//Andrew Schutzbach
//CS 4760
//Project 1
//09/04/2021

#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {

	int ch = 0;
	int time = 0;
	FILE *fp;
	char *fileName;

	if (argc == 1) {
		fileName = "messages.log";
		printf("File name is %s\n", fileName);
	}

	while ((ch = getopt(argc, argv, "h:t")) != -1){
		switch(ch) {
			case 'h':
				printf("Useful info for this program.\n");
				printf("./driver -h: Is a helper message.\n");
				printf("./driver -t seconds: Is for printing messages every second.\n");
			        printf("./driver logfile: Is for changing the file name to where to print.\n";
				printf("All of these can be used at the same time if desired as ./driver -h -t seconds logfile.\n";
				exit(0);
			case 't':
				time = atoi(argv[2]);
				break;
			default:
				break;
		}

	}

	if (argc > 1) {
		fileName = argv[1];
		printf("File name is %s\n", fileName);
	}




}
