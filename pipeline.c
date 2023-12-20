#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipeline.h"

void execute_pipeline(char *commands[], int num_commands) {
	int pipe_fd[2];
	pid_t child_pid;

	if (pipe(pipe_fd) == -1) {	//create pipe
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if((child_pid = fork()) == -1) { //create child process
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0) { //child process
		close(pipe_fd[1]); //close pipe
		dup2(pipe_fd[0], STDIN_FILENO);	//dupe read end of pipe
		close(pipe_fd[0]);	//close the unused read end
		execvp(commands[num_commands], commands + num_commands);	//ex 2nd command in pipeling 
		perror("execvp");	//if execvp fails
		exit(EXIT_FAILURE);
	}
	else {
		close(pipe_fd[0]); //close pipe
		dup2(pipe_fd[1], STDOUT_FILENO);	//dupe write end of pipe
		close(pipe_fd[1]);	//close unused write end
		execvp(commands[0], commands);	//execute the first command 

		perror("execvp");	//if execvp fails
		exit(EXIT_FAILURE);
	}
}

