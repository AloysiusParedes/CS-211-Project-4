/* Functions in file:
	addToList()
	doesNameExist()
	updateStatus()
	retrieveAndRemove()
	countGroupsAhead()
	displayGroupSizeAhead()
	displayListInformation()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurantWaitingListSystem.h"

extern debugMode;

/* add a new node to the end of the list */
void addToList(waitlist **head, char *name, int size, status status){
	//create new node and set the values
	waitlist *new = (waitlist *) malloc(sizeof(waitlist)); 
	new->name = name;
	new->groupSize = size;
	if(status == waiting)
		new->status = waiting;
	else
		new->status = called;
	
	new->next = NULL;
	
	//check if list is empty
	if(*head == NULL){
		*head = new; //set the new node as the head
		return;
	}
	//list not empty
	else{
		waitlist *temp = *head; //used to traverse
		while(temp->next != NULL) //travers until you reach the end of the list
			temp = temp->next;
		temp->next = new; //set the back to the new node
		return;
	}
	
	return;
}

/* returns true if a name already exists in the linked list */
int doesNameExist(waitlist **head, char *name){
	waitlist *temp = *head;
	//check if list is empty
	if(temp == NULL)
		return 0;
	//loop until reach end of list
	while(temp != NULL){
		if(strcmp(temp->name, name) == 0)
			return 1;
		temp = temp->next;
	}
	return 0;
}

/* change in-restaurant status when a call-ahead group arrives
   at the restaurent. Will return false if that group is already
   marked as being in the restaurant. */
boolean updateStatus(waitlist **head, char *name, int debugMode){
	int i = 1;
	waitlist *temp = *head;
	if(temp == NULL){
		printf("List Empty: Can't Update\n");
		return FALSE;
	}
	if(debugMode == TRUE)
		printf("DEBUG MODE\n#\tName\tSize\tStatus\n");
	
	//loop until name is found on the list
	while(temp != NULL){
		if(debugMode == TRUE){
			char *stat;
			if(temp->status == waiting)
				stat = "Present";
			else
				stat = "Not Present";
			printf("%d\t%s\t%d\t%s\n", i, temp->name, temp->groupSize, stat);
			i++;
		}
		if(strcmp(temp->name, name) == 0){
			if(temp->status == waiting)
				return FALSE;
			else{
				temp->status = waiting;
				return TRUE;
			}
		}
		temp = temp->next;
	}
	return FALSE;
}

/* find the first in-restaurant group that can fit at a given table.
   return the name of the group. group is then removed from the list */
void retrieveAndRemove(waitlist **head, int table, int debugMode){
	waitlist *temp = *head;
	waitlist *p;
	int i = 1;
	//list is empty
	if(temp == NULL){
		printf("List empty\n");
		return;
	}
	
	//check front
	if(temp->groupSize <= table && temp->status == 0){
		*head = (*head)->next;
		free(temp);
		if(debugMode == TRUE){
			displayListInformation(head);
		}
		return;
	}
	
	
	if(debugMode == TRUE)
		printf("DEBUG MODE\n#\tName\tSize\tStatus\n");
	
	//check the rest
	while(temp->next != NULL){
		if(debugMode == TRUE){
			char *stat;
			if(temp->status == waiting)
				stat = "Present";
			else
				stat = "Not Present";
			printf("%d\t%s\t%d\t%s\n", i, temp->name, temp->groupSize, stat);
			i++;
		}
		if(temp->next->groupSize <= table){
			if(temp->next->status == 0){
				p = temp->next;
				temp->next = p->next;
				
				free(p);
				return;
			}
		}
		temp = temp->next;
	}
	
	printf("No valid group size for table size\n");
	return;
}

/* return the number of groups waiting ahead of a group with a 
   specific name. */
int countGroupsAhead(waitlist **head, char *name, int debugMode){
	waitlist *temp = *head;
	if(temp == NULL)
		return 0;
	int result = 0, i = 1;
	
	
	if(debugMode == TRUE)
		printf("DEBUG MODE\n#\tName\tSize\tStatus\n");
	while(temp != NULL){
		if(debugMode == TRUE){
			char *stat;
			if(temp->status == waiting)
				stat = "Present";
			else
				stat = "Not Present";
			printf("%d\t%s\t%d\t%s\n", i, temp->name, temp->groupSize, stat);
			i++;
		}
		if(strcmp(temp->name, name) == 0){
			return result;
		}
		result++;
		temp = temp->next;
	}
	return 0;
}

/* traverses down the list until a specific group name is encounterd.
   As each node is traversed, print out the group size */
void displayGroupSizeAhead(waitlist **head, int ahead){
	waitlist *temp = *head;
	int counter = 0, i = 1;
	char *stat;
	
	if(temp == NULL){
		printf("List is empty\n");
		return;
	}
	if(counter == ahead){
		printf("First on the list: No groups ahead\n");
		return;
	}
	printf("#\tName\tSize\tStatus\n");
	while(counter != ahead && temp != NULL){
		if(temp->status == waiting)
			stat = "Present";
		else
			stat = "Not Present";
		printf("%d\t%s\t%d\t%s\n", i, temp->name, temp->groupSize, stat);

		i++;
		temp = temp->next;
		counter++;
	}
	return;
}

/* traverses down the list. print out the groups name, size, and 
   in-restaurant status */
void displayListInformation(waitlist **head){
	int i = 1;
	waitlist *temp = *head;
	char *stat;
	if(temp == NULL){
		printf("List is empty\n");
		return;
	}
	printf("#\tName\tSize\tStatus\n");
	while(temp != NULL){
		if(temp->status == waiting)
			stat = "Present";
		else
			stat = "Not Present";
		printf("%d\t%s\t%d\t%s\n", i, temp->name, temp->groupSize, stat);
		i++;
		temp = temp->next;
	}
	return;
}