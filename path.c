#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "path.h"

void cd_command(char* arguments[512]) {
/*if (arguments == NULL) {
chdir(getenv("HOME"));
}
else {
if(chdir(*arguments) != 0) {
perror("cd");
}
}*/
}

void path_command(char* arguments[512], int size) {
static char path[4096] = "";

if(arguments == NULL) {
printf("%s\n", path);
}
else if (strcmp(arguments[1], "+") == 0) {
printf("Argument: %s\n", *arguments);
if(strlen(path) + size + 1  < sizeof(path)) {
strcat(path, ":");
strcat(path, *arguments + 1);
printf("Updated path: %s\n", path);
}
else {
printf("Error: path variable too long\n");
}
}
else if (strcmp(arguments[1], "-") == 0) {
printf("Argument: %s\n", *arguments);
char* start = strstr(path, *arguments + 1);
if (start != NULL) {
char* end = start + size + 1;
if (*end == ':') {
memmove(start, end + 1, strlen(end + 1) + 1);
}
else if (*end == '\0') {
*start = '\0';
}
printf("Updated path: %s\n", path);
}
}
}
