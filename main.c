/* Jalil Fountain
This code implements some basic operations of singly linked list like inserting in the beginning and end, delete operation, and display operation
*/

#include<stdio.h>
#include<stdlib.h>
#include "main.h"
 
 
//this function takes an item and insert it in the linked list pointed by root.
node*  insert_front(node *root, int item)
{
	node *temp;
	temp=(node*)malloc(sizeof(node));
	temp->data=item;
	temp->next=NULL;
	//create a new node and fill-up the node

//if there is no node in the linked list
     if(root==NULL)
	 root=temp;
	else
    //there is an existing linked list, so put existing root after temp
    {
		temp->next=root;//put the existing root after temp
		root=temp;//make the temp as the root!
    }
  return root;

}

void display(node* t)
{
printf("\nPrinting your linked list.......");
while(t!=NULL){
	printf("%d ",t->data);
	t=t->next;
}

}
node* reverse(node* head)
{
  // no need to reverse if head is null
  // or there is only 1 node.
  if(head ==NULL || head->next==NULL){
	return head;
  }
    // If the list is empty or contains only one node, return the head as it is already reversed.
    // Create a pointer to represent the main list, starting from the second node of the original list.
	node *main_list=head->next;
    // Initialize the reversed list with the first node of the original list.
	node *reversed_list=head;
    // Set the 'next' pointer of this node to NULL, as it will become the last node in the reversed list.
	reversed_list->next=NULL;
    // Loop through the remaining nodes in the main list.
while(main_list !=NULL){

	// Temporarily store the current node from the main list.
 	node* temp=main_list;

	// Move the main list pointer to the next node.
  	main_list=main_list->next;

	// Insert the current node (temp) at the beginning of the reversed list.
   	temp->next=reversed_list;
   	reversed_list=temp;

}
    // Return the head of the reversed list.
    return reversed_list;

}

void insertToPlace(node* list, int val, int place) {
	if(list == NULL || place<=1)
    {
        printf("\nList is empty or place is not valid");
        return;

    }
	// Make the new node.
	node* tmp = (node*)malloc(sizeof(node));
	tmp->data = val;
	// Iterate to the spot BEFORE place, the NULL check
	// ensures we donít go off the list if place is too high.
	int cnt = 1;
	while (list->next != NULL && cnt < place-1) //stop before the place
    {
		list = list->next;
		cnt++;
	}
	// Patch in the node.
	tmp->next = list->next;
	list->next = tmp;
}


int main()
{
	node *root=NULL; //very important line. Otherwise all function will fail
	node *t;
	int ch,ele,v, del;
	while(1)
	{
		printf("\nMenu: 1. insert at front, 2. reverse list 3. Insert to place 0. exit: ");
	    scanf("%d",&ch);
		if(ch==0)
		{
			printf("\nGOOD BYE>>>>\n");
			break;
		}
		if(ch==1)
		{
			printf("\nEnter data (an integer): ");
			scanf("%d",&ele);
			root = insert_front(root, ele);

            display(root);

		}
		if(ch==2)
		{
			root = reverse(root);
			printf("List reversed.\n");
			display(root);

		}
		if(ch==3)
		{
		    int place;
			printf("\nEnter data (an integer) and place (>1) separated by space: ");
			scanf("%d %d",&ele, &place);
			insertToPlace(root, ele, place);

            display(root);

		}

	}
  return 0;
}