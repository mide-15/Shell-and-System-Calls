This project was done by Ayomide Adedeji, Zoe Whitley, and Martin Ortega-Alvarez

Ayomide was responsible for the redirection, exit function, and command-line interpreter.

Zoe was responsible for the path, and history.

Martin was responsible for the change directory and pipelining.

This program is best used on a linux operating system

For the command-line interpreter, there's a character array to take in the command, a temp character array to separate the commands between semicolons, and a 2d array hold each command. If there are 2 arguments, then i open the second argument. If it doesn't open, then it prints out an stderr message. The command array reads the inputs. After the commands are put into the arguments array, there's a for loop to execute each command separated by a semicolon. In each loop, it creates a new process and execute the current command depending on the input.

For the redirection function, if the second index is '<', the program calls dup2() for fileno(stdin), close it, and execute the arguments. Same thing for fileno(stdout) if the second index is '>'

For the exit function, the program loops through the command to see inputs "exit". If it's true then it will execute the commands that were with the "exit" command first (if there were any), then terminate the program.

Due to external factors, the program only has the exit and redirection built-in commands, but you can still use the regular linux commands.
