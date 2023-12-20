#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "redirection.h"
#include "exitcmd.h"
#include "path.h"
#include "chdir.h"
#include "pipeline.h"
//#include "history.h"

int main(int argc, char *argv[]){
	char command[512]; //the command the user wants to make
	char *temp[512];
	char *arguments[512][512]; //the arguments of the command
	int size[512];
	FILE* fptr;
	
	if( argc == 2 ) {
	  fptr = fopen(argv[1], "r");
	  if (fptr == NULL) {
        fprintf(stderr, "The batch file does not exist or cannot be opened.\n");
        exit(0);
	   }
	}
	
	while(1){
		if(argc == 2){
			fgets(command, 512, fptr);
			if(command[strlen(command) - 1] == '\n'){
				command[strlen(command) - 1] = 0;
			}
		}
		else{ printf("prompt> "); fgets(command, 512, stdin); // gets user to input the command
		command[strlen(command) - 1] = 0; // gets rid of the newline
		}
		
		char * tok = strtok(command, ";"); int i = 0;
		while(tok != NULL){
			temp[i] = tok;
			i++;
			tok = strtok(NULL, ";");
		}
		temp[i] = NULL; //sets the last character to a null pointer
		
		for(int l = 0; l < i; l++){
			char * token = strtok(temp[l], " "); int k = 0;
			//puts the arguments into arrays
			while(token != NULL){
				arguments[l][k] = token;
				k++;
				token = strtok(NULL, " ");
			}
			arguments[l][k] = NULL; //sets the last character to a null pointer
			size[l] = k;
		}
		
		for(int index = 0; index < i; index++){
		pid_t pid = fork(); //creates new process
		for(int j = 0; j < size[index]; j++){ // the 'exit' command
			if(strcmp(arguments[index][j], "exit") == 0){
				exitcmd(arguments[index], size[index]); exit(0);
			}
		}
		
		if(pid == 0){ //if the child process was successfully created, then executes the command from the child proceess
			if(strcmp(arguments[index][0], "cd") == 0){
				if(size[index] > 1) {
					change_directory(arguments[index][1]);
				}
				else {
					change_directory(NULL);
				}
				continue;

			}
			if(size[index] > 1){
				if(strcmp(arguments[index][1], "<") == 0 || strcmp(arguments[index][1], ">") == 0 ){
					redirection(arguments[index]);
				}
				if(strcmp(arguments[index][1], "|") == 0){
					if(index != 0) {
						fprintf(stderr, "Error: Pipeline must follow command\n");// call the pipelining function here
						exit(EXIT_FAILURE);
					}
					execute_pipeline(arguments[index], 2);

					exit(0);
				}
			}
			if(strcmp(arguments[index][0], "alias") == 0){
				//add_history(arguments[index]);
			}
			if(strcmp(arguments[index][0], "path") == 0){
				cd_command(arguments[index]);
				path_command(arguments[index], size[index]);
			}
			if(strcmp(arguments[index][0], "myhistory") == 0){
				// call the myhistory function here
			}
			execvp(arguments[index][0], arguments[index]);
			fprintf(stderr, "The command file does not exist or cannot be executed.\n"); exit(0);
		}
		else if(pid > 0){ //if it's a parent, then it will wait for the child
			wait((int *)0);
		}
		}
	}
	fclose(fptr);
	return 0;
}
