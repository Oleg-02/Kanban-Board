#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"


int main() { 
    int choice;
    char blank[] = "blank";
    FILE *filePointer = NULL;

    List *firstListPtr = malloc(sizeof(List));
    List *test = firstListPtr;
    firstListPtr->prevList = NULL;
    strcpy(firstListPtr->name, blank);
    firstListPtr->firstItem = NULL;

    if (firstListPtr == NULL) {
        perror("Failed to allocate memory");
        fflush(stdout);
        return -1;
    }
    
    do{
    	options();
    	scanf("%d", &choice);
        switch (choice) {
        case 1:
            displayBoard(firstListPtr);
            break;
        case 2:
            loadBoard(filePointer, firstListPtr);
            break;
        case 3:
            editList(firstListPtr);
            break;
        case 4:
        	if(firstListPtr->nextList != NULL){
        		test = firstListPtr->nextList;
        	}
            editBoard(firstListPtr);
            if(test->prevList == NULL){
            	firstListPtr = test ;
            }
            break;
        case 5:
            saveBoard(filePointer);
            break;
        case 6:
            break;
        }
    }
    while(choice != 6);


    return 0;
}



