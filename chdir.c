#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "chdir.h"

void change_directory(char *path) {
    if (path == NULL) {
        //if no argument is passed, change to the user's HOME directory
        char *home = getenv("HOME");
        if (home != NULL) {
            if (chdir(home) != 0) {
                perror("chdir");
            }
        } else {
            fprintf(stderr, "HOME environment variable not set.\n");
        }
    } else {
        //change to the specified directory
        if (chdir(path) != 0) {
            perror("chdir");
        }
    }
}

