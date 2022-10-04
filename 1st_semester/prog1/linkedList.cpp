#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next;
};

class linked_list
{
private:
    node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(int n)
    {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
		void display() {
		  struct node* ptr;
		  ptr = head;
		  while (ptr != NULL) {
				cout<< ptr->data << endl;
				ptr = ptr->next;
		  }
		}
};

int main()
{
    linked_list a;
    a.add_node(1);
    a.add_node(2);
		a.display(); 
    return 0;
}