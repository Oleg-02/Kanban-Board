#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"


void options(){
    printf("\n--------------Menu--------------\n");
    printf("1. Display board\n");
    printf("2. Load board from a file\n");
    printf("3. Edit list\n");
    printf("4. Edit Board\n");
    printf("5. Save board to a file\n");
    printf("6. Quit\n");
    printf("Enter your choice (1-6):\n");
    fflush(stdout);
}

void editOptions(char itemOrList[]){
	    printf("\nOptions\n");
	    printf("1. Edit %s name\n", itemOrList);
	    printf("2. Add new %s\n", itemOrList);
	    printf("3. Delete %s\n", itemOrList);
	    printf("4. Return to menu\n");
	    printf("Enter your choice (1-4):\n");
	    fflush(stdout);
}

void displayBoard(List *firstListPtr){
	List *currentListPtr = firstListPtr;
	Item *currentItemPtr = NULL;

	if(strcmp(firstListPtr->name, "blank") == 0){
		puts("There is no file loaded\n");
		fflush(stdout);
		return;
	}

	while(currentListPtr != NULL){
		printf("%s\n", currentListPtr->name);
		fflush(stdout);
		if(currentListPtr->firstItem == NULL){
			currentListPtr = currentListPtr->nextList;
		} else{
			currentItemPtr = currentListPtr->firstItem;
			while(currentItemPtr != NULL){
				printf("\t%s\n", currentItemPtr->itemName);
				fflush(stdout);
				currentItemPtr = currentItemPtr->nextItem;
			}
			currentListPtr = currentListPtr->nextList;
		}
	}

}



void loadBoard(FILE *filePointer, List *firstListPtr){
    char input[50] = "";
    char read[20] = "";
    int firstList = 0, firstItem = 0;
    List *currentListPtr = firstListPtr;
    Item *currentItemPtr = NULL;

    printf("Enter filename:\n");
    fflush(stdout);
    scanf("%s", input);

    filePointer = fopen(input, "r"); // Opens file for reading

    if (filePointer == NULL) {
        perror("Error opening file");
        fflush(stdout);
        return;
    }

    while(fgets(read, 50, filePointer)){
    	read[strlen(read) - 1] = '\0';
    	if (colonCheck(read) == 1){
    		if(firstList == 0){
    			strcpy(currentListPtr->name, read);
    			firstList = 1;
    		} else{
    			List *nextListPtr = malloc(sizeof(List));
    			currentListPtr->nextList = nextListPtr;
    			nextListPtr->prevList = currentListPtr;
    			currentListPtr = nextListPtr;
    			strcpy(currentListPtr->name, read);
    			currentListPtr->nextList = NULL;
    			currentListPtr->firstItem = NULL;
    			firstItem = 0;
    		}

    	} else {
    		if(firstItem == 0){
    			Item *nextItemPtr = malloc(sizeof(Item));
    			currentItemPtr = nextItemPtr;
    		    currentListPtr->firstItem = currentItemPtr;
    		    currentItemPtr->prevItem = NULL;
    		    strcpy(currentItemPtr->itemName, read);
    		    firstItem = 1;
    		} else{
    		    Item *nextItemPtr = malloc(sizeof(Item));
    		    currentItemPtr->nextItem = nextItemPtr;
    		    nextItemPtr->prevItem = currentItemPtr;
       			currentItemPtr = nextItemPtr;
     			strcpy(currentItemPtr->itemName, read);
     			currentItemPtr->nextItem = NULL;
    		}
    	}
    }
    fclose(filePointer);
}

void editList(List *firstListPtr){
	char input[50] = "";
	List *currentListPtr = firstListPtr;

    printf("Enter the name of the list to edit:(include colon)\n");
    fflush(stdout);

    clearBuffer();
    fgets(input, 50, stdin);
    input[strlen(input) - 2] = '\0';
    while(currentListPtr != NULL){
    	if(strcmp(currentListPtr->name, input) == 0 ){
    		editItems(currentListPtr, currentListPtr->firstItem);
    		return;
    	}
    	currentListPtr = currentListPtr->nextList;
    }
    puts("Can't find list, returning to main menu");
    return;
}

void editItems(List *currentListPtr, Item *firstItem){
	int choice = 0;
	char input[50];

	editOptions("item");

	scanf("%d", &choice);
	clearBuffer();

    switch (choice) {
     case 1:
    	itemActions(currentListPtr, firstItem, "edit");
        break;
     case 2:

    	puts("Enter the name of the item to add:");
    	fflush(stdout);
    	fgets(input, 50, stdin);
    	input[strlen(input) - 2] = '\0';

    	Item *new = malloc(sizeof(Item));

    	if(currentListPtr->firstItem == NULL){
    		new->prevItem = NULL;
    		new->nextItem = NULL;
    		strcpy(new->itemName, input);
    		currentListPtr->firstItem = new;
    	} else{
    		currentListPtr->firstItem->prevItem = new;
    		new->nextItem = currentListPtr->firstItem;
    		new->prevItem = NULL;
    		strcpy(new->itemName, input);
    		currentListPtr->firstItem = new;
    	}
        break;
     case 3:
    	itemActions(currentListPtr, firstItem, "delete");
        break;
     case 4:
    	return;
     default:
    	editItems(currentListPtr, firstItem);
    	return;
    }

}

void itemActions(List *currentListPtr, Item *firstItem, char todo[]){
	char input[50];
	Item *currentItemPtr = firstItem;

	printf("Enter the name of the item to %s:\n", todo);
	fflush(stdout);
	fgets(input, 50, stdin);
	input[strlen(input) - 2] = '\0';
	while(currentItemPtr != NULL){
	    	if(strcmp(currentItemPtr->itemName, input) == 0 ){
	    		if(strcmp(todo, "delete") == 0 ){
	    			itemDelete(currentListPtr, firstItem, currentItemPtr);
	    			puts("Successfully deleted");
	    			fflush(stdout);
	    			return;
	    		} else{
	    			printf("Enter new name for %s:\n", currentItemPtr->itemName);
	    			fflush(stdout);
	    			fgets(input, 50, stdin);
	    			input[strlen(input) - 2] = '\0';
	    			strcpy(currentItemPtr->itemName, input);
	    			return;
	    		}
	    	}
	    	currentItemPtr = currentItemPtr->nextItem;
	    }
}

void itemDelete(List *currentListPtr, Item *firstItem, Item *currentItemPtr){
	if(currentItemPtr->prevItem == NULL && currentItemPtr->nextItem == NULL){
		currentListPtr->firstItem = NULL;
	}else if(currentItemPtr->prevItem == NULL){
		currentListPtr->firstItem = currentItemPtr->nextItem;
		currentItemPtr->nextItem->prevItem = NULL;
		free(currentItemPtr);
		return;
	}else if(currentItemPtr->nextItem == NULL){
		currentItemPtr->prevItem->nextItem = NULL;
		free(currentItemPtr);
		return;
	} else{
		currentItemPtr->nextItem->prevItem = currentItemPtr->prevItem;
		currentItemPtr->prevItem->nextItem = currentItemPtr->nextItem;
		free(currentItemPtr);
		return;
	}
}

void editBoard(List *firstListPtr){
	int choice = 0;
	char input[50];
	List *currentPtr = firstListPtr;
	editOptions("board");

	scanf("%d", &choice);
	clearBuffer();

	switch(choice){
	case 1:
		listActions(firstListPtr, "edit");
		break;
	case 2:
    	puts("Enter the name of the list to add:");
    	fflush(stdout);
    	fgets(input, 50, stdin);
    	input[strlen(input) - 2] = '\0';

    	List *new = malloc(sizeof(List));
    	strcpy(new->name, input);
    	currentPtr->nextList->prevList = new;
    	new->nextList = currentPtr->nextList;
    	new->prevList = currentPtr;
    	currentPtr->nextList = new;
    	break;
	case 3:
		listActions(firstListPtr, "delete");
		break;
	case 4:
		return;
	default:
		editBoard(firstListPtr);
		return;
	}
}

void listActions(List *firstListPtr, char todo[]){
	char input[50];
	List *currentListPtr = firstListPtr;

	printf("Enter the name of the list to %s:\n", todo);
	fflush(stdout);
	fgets(input, 50, stdin);
	input[strlen(input) - 2] = '\0';
	while(currentListPtr != NULL){
	    	if(strcmp(currentListPtr->name, input) == 0 ){
	    		if(strcmp(todo, "delete") == 0 ){
	    			listDelete(currentListPtr, firstListPtr);
	    			puts("Successfully deleted");
	    			fflush(stdout);
	    			return;
	    		} else{
	    			printf("Enter new name for %s:\n", currentListPtr->name);
	    			fflush(stdout);
	    			fgets(input, 50, stdin);
	    			input[strlen(input) - 2] = '\0';
	    			strcpy(currentListPtr->name, input);
	    			return;
	    		}
	    	}
	    	currentListPtr = currentListPtr->nextList;
	    }

}

void listDelete(List *currentListPtr, List *firstListPtr){
	if(currentListPtr->prevList == NULL){
		puts("no");
		fflush(stdout);
		currentListPtr->nextList->prevList = NULL;
		puts("no");
		fflush(stdout);
		free(currentListPtr);
		return;
	}else if(currentListPtr->nextList == NULL){
		currentListPtr->prevList->nextList = NULL;
		free(currentListPtr);
		return;
	} else{
		currentListPtr->nextList->prevList = currentListPtr->prevList;
		currentListPtr->prevList->nextList = currentListPtr->nextList;
		free(currentListPtr);
		return;
	}
}

void saveBoard(FILE *filePointer){
    FILE *here;

    here = fopen("test.txt", "w");

    fprintf(here, "hello World");
    fclose(here);

}

int colonCheck(char sentence[]){
	int i = 0;

	while(sentence[i] != 0){
		if(sentence[i] == 58) {
			return 1;
		}
		i++;
	}

	return 0;
}

void clearBuffer(){
	int c;
	while( (c = getchar()) != '\n') {}
}
