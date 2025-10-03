typedef struct Item {
    char itemName [50];
    struct Item *prevItem;
    struct Item *nextItem;
}Item;

typedef struct List {
    char name [50];
    struct Item *firstItem;
    struct List *prevList;
    struct List *nextList;
}List;

void options();
void editOptions(char[]);
void loadBoard(FILE *filePointer, List *firstListPtr);
void editList(List *firstListPtr);
void editItems(List *currentListPtr, Item *firstItem);
void itemActions(List *currentListPtr, Item *firstItem, char todo[]);
void itemDelete(List *currentListPtr, Item *firstItem, Item *currentItemPtr);
void editBoard(List *firstListPtr);
void listActions(List *firstListPtr ,char todo[]);
void listDelete(List *currentListPtr, List *firstListPtr);
void saveBoard();
void displayBoard(List *firstListPtr);
void clearBuffer();
int colonCheck(char sentence[]);


