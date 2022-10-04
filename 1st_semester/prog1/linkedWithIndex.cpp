// Simple C++ program to 
// find n'th node from end 
#include<iostream> 
using namespace std; 

struct node 
{ 
int data; 
struct node* next; 
}; 

/* Function to get the nth node 
from the last of a linked list*/
void printNthFromLast(struct node *head, int n) 
{ 
struct node *main_ptr = head; 
struct node *ref_ptr = head; 

int count = 0; 
if(head != NULL) 
{ 
	while( count < n ) 
	{ 
		if(ref_ptr == NULL) 
		{ 
		printf("%d is greater than the no. of "
					"nodes in list", n); 
		return; 
		} 
		ref_ptr = ref_ptr->next; 
		count++; 
	}
	
	if(ref_ptr == NULL) 
	{ 
		head = head->next; 
		if(head != NULL) 
			printf("node no. %d from last is %d ", n, main_ptr->data); 
	} 
	else
	{ 
	while(ref_ptr != NULL) 
	{ 
		main_ptr = main_ptr->next; 
		ref_ptr = ref_ptr->next; 
	} 
	printf("node no. %d from last is %d ", n, main_ptr->data); 
	} 
} 
} 

// Function to push 
void push(struct node** head_ref, int new_data) 
{ 
/* allocate node */
struct node* new_node = new node(); 

/* put in the data */
new_node->data = new_data; 

/* link the old list off the new node */
new_node->next = (*head_ref);	 

/* move the head to point to the new node */
(*head_ref) = new_node; 
}

int main() 
{ 
struct node* head = NULL; 
push(&head, 20); 
push(&head, 4); 
push(&head, 15); 
push(&head, 35); 

printNthFromLast(head, 4); //Node no. 4 from last is 35
}
