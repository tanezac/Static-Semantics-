// Project 3 - Static Semantics
// p3.c
// Tan Nguyen
// ntnhmc@umsystem.edu
// Apr 18, 2022


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "scanner.h"
#include "testTree.h"
#include "parser.h"
#include "node.h"
#include "statSem.h"
#include "identifierStack.h"

void help();  // display information about how to run program

int main(int argc, char **argv) {

	// ERROR if there are more than 2 arguments
	if (argc > 2) {
		printf("Error: Expected 1 or no arguments\n");
		printf("Try './frontEnd -h' for more information.\n");
		return EXIT_FAILURE;
	}

	int opt;
        while((opt = getopt(argc, argv, "h")) != -1){
        	switch(opt)
        	{
			case 'h':
                		help();
                		exit(EXIT_SUCCESS);
                		break;
			case '?':
				printf("Unknown option: %c\n", opt);
                		break;
            		default:
                		perror("oss.c: error: invalid argument");
                		help();                		
				break;
       		}
        }

   	FILE *inFilePtr = NULL;
    	char *fileName = NULL;
	node_t *tree;

	//Read from file if argument = 2 and Read from the keyboard
	if (argc == 2) {
        	const char fileExt[] = ".txt";
        	fileName = (char *) malloc(sizeof(argv[1]));
        	strcpy(fileName, argv[1]);
        	char inFile[strlen(fileName) + strlen(fileExt)];	// add ".txt" into fileName : fileName.txt
        	strcpy(inFile, fileName);
        	strcat(inFile, fileExt);

		inFilePtr = fopen(inFile, "r");
		
		// if file error, abort with appropriate message 
		if (!inFilePtr) {
			printf("Error: File %s could not be opened\n", inFile);
			return (EXIT_FAILURE);
		}

		if(!feof(inFilePtr)){
			tree = parser(inFilePtr);
		}
		printf("Semantic Check Started\n");
		stackInit();
		semanticCheck(tree);
 	  	printf("Semantic Check Complete\n");
		
		print_stack();
		preOrderPrint(tree);
	}
	//Read from Keyboard until EOF, the CTRL + D
	else {
		inFilePtr = stdin;
		if (inFilePtr == NULL){
			fprintf(stderr, "Unable To Start stdin: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if(!feof(inFilePtr)){
			tree = parser(inFilePtr);
		}
		printf("Semantic Check Started\n");
		stackInit();
		semanticCheck(tree);
 	  	printf("Semantic Check Complete\n");

		print_stack();
		preOrderPrint(tree);
	}

	//testScanner(inFilePtr);
    	fclose(inFilePtr);
	free(fileName);
	return 0;
}

//Print how to run program
void help(){
	printf("\n------------------------------------------------------------------------------------\n");
	
	printf("How to implement program::  \n");
	printf("Invocation:  ./statSem [file]  \n");
	printf("There are three ways to run the program: \n");
	printf("1. ./statSem to prompt user to enter from keyboard. \n");
	printf("2. ./statSem < [filename] to direct inout file to scanner exectuable program. \n");
	printf("3. ./statSem [filename] // without .input suffix in file name. \n");

	printf("--------------------------------------------------------------------------------------\n\n");

}
