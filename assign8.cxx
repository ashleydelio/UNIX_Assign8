/* *********************************************
 * Programmer Name: Ashley De Lio
 * 
 * Z-ID: Z1723695
 * 
 * Class: CSCI 330 - 2
 * 
 * Program:  Assignment 8
 * 
 * Purpose: 
 * ********************************************/
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>



using namespace std;

int main() {	

	
	
//While loop to continue processing commands until "exit" command is entered	
	while(true) {
	
	char buffer[250];
	string command;
	string argument1, argument2, argument3, argument4;
	
	
//Prompt user for command and place entered command, options, and arguments into buffer	
	cout << "Enter command: ";
	cin.getline(buffer, 250);

//If user entered "exit" command, break out of loop	
	if(!strcmp(buffer, "exit")) {
		break;
	}
	
//Begin process to divide inputed string into command, options, and arguments	
	
//Define deliminator and new array for command, options, and arguments to be placed into	
	const char delim[2] = " ";
	char * section[5];
	int curSect = 0;
	char *token;
	
	token = strtok(buffer, delim);

//Place	pieces of buffer (separated by whitespace) into section array and corresponding command, options, and arguments arrays
	while (token != NULL){
		section[curSect] = (char *) malloc  (strlen(token) + 1);
		strcpy(section[curSect], token);

//First string entered by user is command		
		if (curSect == 0){
			command = section[curSect];
		}

//If a string entered by a user does not start with "-" and is not the first string, then it gets copied to the arguments array	
		else if (curSect == 1){
			argument1 = section[curSect];
		}
		
		else if (curSect == 2){
			argument2 = section[curSect];
		}
		
		else if (curSect == 3){
			argument3 = section[curSect];
		}
		
		else if (curSect == 4){
			argument4 = section[curSect];
		}
		
		curSect++;
		
		token = strtok(NULL, delim);
	}
	
//Fork process 		
	int pid, rs, status;
	
	pid = fork();
	
//If fork fails, exit with error message	
	if (pid == -1) { 
		perror("fork"); 
		exit(EXIT_FAILURE); 
	}

// Child process: execlp to command with options and arguments 
	if (pid == 0) {

//Set of if statements to determine how many options and/or arguments have been entered and pass the proper number of arguments to execlp				
		
		//If no options or arguments were entered
		if (curSect == 1){
			rs = execlp(command.c_str(), command.c_str(), (char*) NULL);
			if (rs == -1) { 
				perror(command.c_str()); exit(EXIT_FAILURE); 
			}
		
		}
		
		//If one option or argument was entered
		if (curSect == 2){
			rs = execlp(command.c_str(), command.c_str(), argument1.c_str(), (char*) NULL);
			if (rs == -1) { 
				perror(command.c_str()); exit(EXIT_FAILURE); 
			}
		
		}
	 
		//If two options and/or arguments were entered
		if (curSect == 3){
			rs = execlp(command.c_str(), command.c_str(), argument1.c_str(), argument2.c_str(), (char*) NULL);
			if (rs == -1) { 
				perror(command.c_str()); exit(EXIT_FAILURE); 
			}
		
		}
		
		//If three options and/or arguments were entered
		if (curSect == 4){
			rs = execlp(command.c_str(), command.c_str(), argument1.c_str(), argument2.c_str(), argument3.c_str(), (char*) NULL);
			if (rs == -1) { 
				perror(command.c_str()); exit(EXIT_FAILURE); 
			}
		
		}
		
		//If four options and/or arguments were entered
		if (curSect == 5){
			rs = execlp(command.c_str(), command.c_str(), argument1.c_str(), argument2.c_str(), argument3.c_str(), argument4.c_str(), (char*) NULL);
			if (rs == -1) { 
				perror(command.c_str()); exit(EXIT_FAILURE); 
			}
		
		}
	}
// Parent process: wait for child to end
	else { 
      wait(&status);
	}
   	
		
	}

	return 0;
}	
