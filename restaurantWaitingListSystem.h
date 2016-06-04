/* header file to connect the 3 source files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;
typedef enum {waiting = 0, called = 1} status;

typedef struct node{
	char *name;
	int groupSize;
	status status;
	struct node *next;
} waitlist;

/* FUNCTION PROTOTYPES */
/* userInterface.c */
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void printCommands();

/* linkedListFunctions.c */
void doAdd(waitlist **head, int debugMode);
void doCallAhead(waitlist **head, int debugMode);
void doWaiting(waitlist **head, int debugMode);
void doRetrieve(waitlist **head, int debugMode);
void doList(waitlist **head, int debugMode);
void doDisplay(waitlist **head);

/* linkedListImp.c */
void addToList(waitlist **head, char *name, int size, status status);
int doesNameExist(waitlist **head, char *name);
boolean updateStatus(waitlist **head, char *name, int debugMode);
void retrieveAndRemove(waitlist **head, int table, int debugMode);
int countGroupsAhead(waitlist **head, char *name, int debugMode);
void displayGroupSizeAhead(waitlist **head, int ahead);
void displayListInformation(waitlist **head);