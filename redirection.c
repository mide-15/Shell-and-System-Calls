#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "redirection.h"

void redirection(char* arguments[512]){
	if(strcmp(arguments[1], "<") == 0){
		int ifp = open(arguments[2], O_RDONLY);
		dup2(ifp, fileno(stdin));
		close(ifp);
		execlp(arguments[0], arguments[0], NULL);
	}
	if(strcmp(arguments[1], ">") == 0){
		int ofp = open(arguments[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		dup2(ofp, fileno(stdout));
		close(ofp);
		execlp(arguments[0], arguments[0], NULL);
	}
}	