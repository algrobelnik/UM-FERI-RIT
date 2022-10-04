#include <iostream>

using namespace std;

struct node {
  int data;
  node *next;
};

class linked_list {
private:
  node *head, *tail;

public:
  linked_list() {
    head = NULL;
    tail = NULL;
  }

  void add_node(int d) {
    node *tmp = new node;
    tmp->data = d;
    tmp->next = NULL;

    if (head == NULL) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tail->next;
    }
  }

  void add_node_after(int d, node *ptr) {
    node *tmp = new node;
    tmp->data = d;
    tmp->next = ptr->next;
    ptr->next = tmp;

    if (tail == ptr) {
      tail = tmp;
    }
  }

  void delete_node() {
    node *tmp = head;
    head = head->next;
    if (tail == tmp) {
      tail == NULL;
    }
    delete tmp;
  }

  void delete_node_after(node *ptr) {
    node *tmp = new node;
    tmp = ptr->next;
    ptr->next = tmp->next;

    if (tail == tmp) {
      tail = ptr;
    }
    delete tmp;
  }

  node *search(int d) {
    node *tmp = head;
    while (tmp != NULL && d != tmp->data) {
      tmp = tmp->next;
    }
    return tmp;
  }

  void display() {
    struct node *tmp;
    tmp = head;
    while (tmp != NULL) {
      cout << tmp->data << endl;
      tmp = tmp->next;
    }
    cout << endl;
  }
};

int main() {
  linked_list a;
  cout << "Add random nodes." << endl;
  a.add_node(1);
  a.add_node(5);
  a.display();
  node *p = a.search(1);
  cout << "Add node after p pointer." << endl;
  a.add_node_after(3, p);
  a.display();
  cout << "Add random nodes." << endl;
  a.add_node(6);
  a.add_node(7);
  a.display();
  cout << "Delete head value in my case 1." << endl;
  a.delete_node();
  a.display();
  p = a.search(6);
  cout << "Delete node after pointer p." << endl;
  a.delete_node_after(p);
  a.display();
  cout << "Add random nodes." << endl;
  a.add_node(9);
  a.display();
  return 0;
}