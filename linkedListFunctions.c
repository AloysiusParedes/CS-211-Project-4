/* Functions within file:
	doAdd()
	doCallAhead()
	doWaiting()
	doRetrieve()
	doList()
	doDisplay()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurantWaitingListSystem.h"

extern debugMode;

void doAdd(waitlist **head, int debugMode){
	/* get group size from input */
	int size = getPosInt();
	if(size < 1){
		printf("Error: Add command requires an integer value of at least 1\n");
		printf("Add command is of form: a <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if(NULL == name){
		printf("Error: Add command requires a name to be given\n");
		printf("Add command is of form: a <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}
	// add code to perform this operation here
	
	//check if the name already exists in the waitlist
	if(doesNameExist(head, name)){
		printf("Name already exists in the wait list\n");
		return;
	}
 	//add to back of the list
	else{ 
		if(debugMode == TRUE){
			displayListInformation(head);
		}
		printf("Adding group \"%s\" of size %d\n", name, size);
		addToList(head, name, size, waiting);
		return;
	} 
}

void doCallAhead(waitlist **head, int debugMode){
	/* get group size from input */
	int size = getPosInt();
	if(size < 1){
		printf ("Error: Call-ahead command requires an integer value of at least 1\n");
		printf ("Call-ahead command is of form: c <size> <name>\n");
		printf ("  where: <size> is the size of the group making the reservation\n");
		printf ("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name){
		printf ("Error: Call-ahead command requires a name to be given\n");
		printf ("Call-ahead command is of form: c <size> <name>\n");
		printf ("  where: <size> is the size of the group making the reservation\n");
		printf ("         <name> is the name of the group making the reservation\n");
		return;
	}

	// add code to perform this operation here
	
	//check if the name already exists in the waitlist
	if(doesNameExist(head, name)){ 
		printf("Name already exists in the wait list\n");
		return;
	}
	else{
		if(debugMode == TRUE){
			displayListInformation(head);
		}
		printf ("Call-ahead group \"%s\" of size %d\n", name, size);
		addToList(head, name, size, called);
		return;
	}
}

void doWaiting(waitlist **head, int debugMode){
	/* get group name from input */
	char *name = getName();
	if (NULL == name){
		printf ("Error: Waiting command requires a name to be given\n");
		printf ("Waiting command is of form: w <name>\n");
		printf ("  where: <name> is the name of the group that is now waiting\n");
		return;
	}

	printf ("Waiting group \"%s\" is now in the restaurant\n", name);

	// add code to perform this operation here
	if(!doesNameExist(head, name)){ 
		if(debugMode == TRUE){
			displayListInformation(head);
		}
		printf("Name does not exist wait list\n");
		return;
	}
	if(updateStatus(head, name, debugMode) == FALSE){
		return;
	}
	else{
		updateStatus(head, name, debugMode);
		return;
	}
	
}

void doRetrieve(waitlist **head, int debugMode){
	/* get table size from input */
	int size = getPosInt();
	if (size < 1){
		printf ("Error: Retrieve command requires an integer value of at least 1\n");
		printf ("Retrieve command is of form: r <size>\n");
		printf ("  where: <size> is the size of the group making the reservation\n");
		return;
	}
	clearToEoln();
	printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

	// add code to perform this operation here
	retrieveAndRemove(head, size, debugMode);
	return;
	
}

void doList(waitlist **head, int debugMode){
	/* get group name from input */
	char *name = getName();
	if (NULL == name){
		printf ("Error: List command requires a name to be given\n");
		printf ("List command is of form: l <name>\n");
		printf ("  where: <name> is the name of the group to inquire about\n");
		return;
	}

	// add code to perform this operation here
	
	//check if the name already exists in the waitlist
	if(doesNameExist(head, name)){
		printf("Number of groups ahead of \"%s\": %d\n", name, countGroupsAhead(head, name, debugMode));
		
		printf ("Group \"%s\" is behind the following groups\n", name);
		//list size of each group
		displayGroupSizeAhead(head, countGroupsAhead(head, name, debugMode));
		return;
	}
 	//add to back of the list
	else{
		printf("Name does not exist in list\n");
		return;
	}
	
	
}

void doDisplay(waitlist **head){
	clearToEoln();
	printf ("Display information about all groups\n");

	// add code to perform this operation here
	displayListInformation(head);
}