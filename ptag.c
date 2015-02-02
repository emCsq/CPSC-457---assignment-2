#include <linux/kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>

#define __NR_ptag 337		//imports the system call

int main(int argc, char* argv[]){
	int flags = 0, opt = 0;
	int rand, check;
	int method = 0; //0 = add, 1 = remove
	long pid;
	
	pid = strtol(argv[1], NULL, 10);		//retrieves pid from cmd and convert to long
	check = kill(pid);
	if (check == -1) {				//checks if valid pid else break program
		printf("Error: Unable to trace.\n");
		exit(1);
	}
	
	char * tag = argv[3];				//retrieve tag from user and put in variable

	while ((opt = getopt(argc, argv, "a:r")) != -1){	//uses getopt to determine whether or not we'll be adding or removing a tag
		switch(opt){					//this is done in a switch
			case 'a':				//in the case of add, set variable to 0
				method = 0;
				break;
			case 'r':
				method = 1;			//in the case of remove, set variable to 1
				break;
			default:
				method = -1;			//in the case where there is neither, break program with error message
				printf("Error: No add/remove instruction was given.\n");
				exit(1);
		}
	}

	syscall(__NR_ptag, pid, tag, method); 			//system call with the given parameters
	
}
