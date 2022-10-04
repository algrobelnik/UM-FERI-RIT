#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <cmath>

struct node {
  int data;
  node *next, *prev;
};

class linked_list {
private:
  node *head, *tail;

public:
  linked_list() {
    head = NULL;
    tail = NULL;
  }

  void add_node_head(int d) {
    node *tmp = new node;
    tmp->data = d;
    tmp->prev = NULL;
    tmp->next = head;

    if (head == NULL) {
      tail = tmp;
    } else {
      head->prev = tmp;
    }

    head = tmp;
  }

  void add_node_tail(int d) {
    node *tmp = new node;
    tmp->data = d;
    tmp->next = NULL;
    tmp->prev = tail;

    if (head == NULL) {
      head = tmp;
    } else {
      tail->next = tmp;
    }

    tail = tmp;
  }

  void sum_head_to_tail() {
    long long vsota = 0;
    node *tmp = head;
    while (tmp != NULL) {
      vsota += tmp->data;
      tmp = tmp->next;
    }
    std::cout << "Sum: " << vsota << std::endl;
  }

  void delete_node(node *ptr) {
    if (ptr->prev == NULL && ptr->next == NULL) {
      head = NULL;
      tail = NULL;
    } else {
      if (ptr->prev == NULL) {
        head = ptr->next;
        head->prev = NULL;
      } else {
        ptr->prev->next = ptr->next;
      }
      if (ptr->next == NULL) {
        tail = ptr->prev;
        tail->next = NULL;
      } else {
        ptr->next->prev = ptr->prev;
      }
    }
    delete ptr;
  }

  void delete_node_all() {
    node *tmp = head;
    if (tmp == NULL) {
      return;
    }
    while (tmp != NULL) {
      tmp = tmp->next;
      delete_node(head);
    }
  }

  bool check_if_sorted() {
    node *tmp = head;
    if (tmp == NULL) {
      return true;
    }
    while (tmp->next != NULL) {
      if (tmp->data > tmp->next->data)
        return false;
      tmp = tmp->next;
    }
    return true;
  }

  node *search(int d) {
    node *tmp = head;
    while (tmp != NULL && d != tmp->data) {
      tmp = tmp->next;
    }
    return tmp;
  }

  node *getNode(int count) {
    node *tmp = head;
    for (int i = 0; tmp != NULL && i < count; i++) {
      tmp = tmp->next;
    }
    return tmp;
  }

  void display() {
    node *tmp = head;
    while (tmp != NULL) {
      std::cout << tmp->data << " ";
      tmp = tmp->next;
    }
    std::cout << std::endl;
  }

  node *split(node *t, node *h) {
    int pivot = t->data;
    node *li = t;
    node *ri = h;
    bool cross = false;
    while (!cross) {
      while (li->data <= pivot && li != h) {
        li = li->next;
        if (li == ri)
          cross = true;
      }
      while (ri->data >= pivot && ri != t) {
        ri = ri->prev;
        if (li == ri)
          cross = true;
      }
      if (!cross)
        std::swap(li->data, ri->data);
    }
    std::swap(t->data, ri->data);
    return ri;
  }

  void quickSort(node *t, node *h) {
    if (t != h) {
      node *tmp = split(t, h);
      if (t != tmp)
        quickSort(t, tmp->prev);
      if (h != tmp)
        quickSort(tmp->next, h);
    }
  }

  node *getTail() { return tail; }

  node *getHead() { return head; }
};

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

void generateVecRand(linked_list &list, int num1) {
  list.delete_node_all();
  for (int i = 0; i < num1; i++)
    list.add_node_tail(randGen(1, num1));
}

/* int split(linked_list &list, int a, int b) {
  node *pivot = list.getNode(a);
  int li = a;
  int ri = b;
  while (li < ri) {
    while (list.getNode(li)->data <= pivot->data && li < b)
      li++;
    while (list.getNode(ri)->data >= pivot->data && ri > a)
      ri--;
    if (li < ri)
      std::swap(list.getNode(li)->data, list.getNode(ri)->data);
  }
  std::swap(list.getNode(a)->data, list.getNode(ri)->data);
  return ri;
} */

void menu() {
  std::cout << "======================================" << std::endl;
  std::cout << "================ MENU ================" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "1) Generate random sequence" << std::endl;
  std::cout << "2) Print sequence" << std::endl;
  std::cout << "3) Check if sequence is sorted" << std::endl;
  std::cout << "4) Sum elements in sequence" << std::endl;
  std::cout << "5) Quicksort" << std::endl;
  std::cout << "0) End" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "Select: ";
}

int main() {
  srand(time(nullptr));
  std::chrono::time_point<std::chrono::system_clock> start, end;
  bool running = true;
  int selection, num1;
  int size;
  linked_list list;
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
    case 1: {
      std::cout << "Size: ";
      std::cin >> num1;
      size = num1;
      generateVecRand(list, num1);
      break;
    }
    case 2: {
      list.display();
      break;
    }
    case 3: {
      if (list.check_if_sorted())
        std::cout << "Sequence is sorted" << std::endl;
      else
        std::cout << "Sequence is not sorted" << std::endl;
      break;
    }
    case 4: {
      list.sum_head_to_tail();
      break;
    }
    case 5: {
      if (list.check_if_sorted()) {
        std::cout << "Sequence is sorted";
        break;
      }
      start = std::chrono::system_clock::now();
      list.quickSort(list.getHead(), list.getTail());
      end = std::chrono::system_clock::now();
      std::cout << "elapsed time[µs]: "
                << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                         start)
                       .count()
                << std::endl;
      break;
    }
    case 0:
      running = false;
      break;
    default:
      std::cout << "Wrong selection!" << std::endl;
      break;
    }
    std::cout << std::endl;
  } while (running);
  return 0;
}