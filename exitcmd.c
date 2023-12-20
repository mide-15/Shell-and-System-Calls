#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "exitcmd.h"

void exitcmd(char* arguments[512], int size){
/*	char command[50]; //the command the user wants to makeng
	char *arguments[50]; //the arguments of the commandx
	
	while(1){
	printf("prompt> "); fgets(command, 50, stdin); // gets user to input the command
	char * token = strtok(command, " "); int i = 0;
	command[strlen(command) - 1] = 0; // gets rid of the newline
	
		while(token != NULL){
			arguments[i] = token; //printf("%s", arguments[i]);
			i++;
			token = strtok(NULL, " ");
		}
		arguments[i] = NULL; //sets the last character to a null pointer
		if(strcmp(arguments[i-1], "exit\n") == 0 ){
			arguments[i-1][strlen(arguments[i-1]) - 1] = '\0'; // gets rid of the newline
		}
	if(strcmp(arguments[i-1], "exit") == 0){
		exit(0);
	}
	
	}*/
		int n = 0;
		if(n > 0){
			exit(0);
		}
	
	char *ex[512]; int j = 0;
	for(int i = 0; i < size; i++){
		if(strcmp(arguments[i], "exit") != 0){
			ex[j] = arguments[i];
			j++;
		}
	}
	ex[j] = NULL;
	if(j > 0){
		execvp(ex[0], ex);
	}
	
	//return 0;
}	