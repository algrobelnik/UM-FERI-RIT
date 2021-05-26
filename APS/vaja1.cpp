#include <iostream>

using namespace std;

struct Sklad {
  int *S;
  int vrh;
  int MAX;
};

struct node {
  int data;
  node *next;
};

class linked_list {
private:
  node *head, *tail;
  int max;

public:
  linked_list(int max) {
    head = NULL;
    tail = NULL;
    this->max = max;
  }

  void add_node(int d) {
    node *tmp = new node;
    tmp->data = d;
    tmp->next = NULL;

    if (!countNode()) {
      cout << "Size is full for " << d << endl;
      return;
    }
    if (head == NULL) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tail->next;
    }
  }

  void delete_node() {
    node *tmp = head;
    head = head->next;
    if (tail == tmp)
      tail == NULL;
    delete tmp;
  }

  int countNode() {
    int count = 0;
    node *tmp = head;
    while (tmp != NULL) {
      tmp = tmp->next;
      count++;
    }
    return max - count;
  }

  void pop() {
    cout << head->data << endl;
    head = head->next;
  }

  void displayAll() {
    struct node *tmp;
    tmp = head;
    while (tmp != NULL) {
      cout << tmp->data << endl;
      tmp = tmp->next;
    }
    cout << "Size: " << max << endl;
  }
};

void pushSklad(Sklad &s, int x) {
  if (s.vrh + 1 == s.MAX) {
    cout << "napaka: polno" << endl;
  } else {
    s.vrh++;
    s.S[s.vrh] = x;
  }
}

void popSklad(Sklad &s) {
  if (s.vrh == 0) {
    cout << "napaka: prazno" << endl;
  } else {
    s.vrh--;
    cout << s.S[s.vrh + 1] << endl;
  }
}

int main() {
  Sklad s;
  s.MAX = 3;
  s.S = new int[s.MAX];
  s.vrh = -1;
  pushSklad(s, 1);
  pushSklad(s, 2);
  pushSklad(s, 3);
  pushSklad(s, 4);
  popSklad(s);

  for (int i = 0; i < s.vrh + 1; i++)
    cout << s.S[i] << endl;

  linked_list a(2);
  // Adding random nodes
  a.add_node(1);
  a.add_node(2);
  a.add_node(3);
  a.add_node(4);
  cout << "Izpis prvih dveh elementov: " << endl;
  a.pop();
  a.pop();
  a.add_node(5);
  a.add_node(6);
  cout << "Vsi elementi: " << endl;
  a.displayAll();
  return 0;
}