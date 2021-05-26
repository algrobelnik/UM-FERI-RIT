#include <chrono>
#include <iostream>

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

  void add_node_after(int d, node *ptr) {
    node *tmp = new node;
    tmp->data = d;
    tmp->prev = ptr;
    tmp->next = ptr->next;
    ptr->next = tmp;

    if (tail == ptr) {
      tail = tmp;
    } else {
      tmp->next->prev = tmp;
    }
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
      std::cout << tmp->data << std::endl;
      tmp = tmp->next;
    }
    std::cout << std::endl;
  }

  void rdisplay() {
    struct node *tmp;
    tmp = tail;
    while (tmp != NULL) {
      std::cout << tmp->data << std::endl;
      tmp = tmp->prev;
    }
    std::cout << std::endl;
  }
};

int *add_to_head_array(int length) {
  int *array = new int[length];
  for (int i = 0; i < length; i++) {
    for (int j = 0; j - 1 < i; j++) {
      array[i - j + 1] = array[i - j];
    }
    array[0] = i + 1;
  }
  return array;
}

void menu() {
  std::cout << "======================================" << std::endl;
  std::cout << "================ MENU ================" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "1) Iskanje podatka" << std::endl;
  std::cout << "2) Vnos podatka v glavo" << std::endl;
  std::cout << "3) Vnos podatka za elementom" << std::endl;
  std::cout << "4) Vnos podatka za repom" << std::endl;
  std::cout << "5) Brisanje podatka" << std::endl;
  std::cout << "6) Izpis seznama od glave proti repu" << std::endl;
  std::cout << "7) Izpis seznama od repa proti glavi" << std::endl;
  std::cout << "8) Testiraj hitrost" << std::endl;
  std::cout << "0) Konec" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "Select: ";
}

int main() {
  /* linked_list a;

  std::cout << "Adding random nodes." << std::endl;
  a.add_node_head(1);
  a.add_node_tail(5);
        node *p = a.search(1);
  a.add_node_after(2, p);
        p = a.search(2);
  a.add_node_after(3, p);
        p = a.search(3);
  a.add_node_after(4, p);
  a.display();
  a.rdisplay();
  p = a.search(3);
        a.delete_node(p);
  p = a.search(1);
        a.delete_node(p);
  p = a.search(5);
        a.delete_node(p);
        a.display();
  a.rdisplay(); */
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  std::time_t end_time;
  bool running = true;
  int selection, num1, num2;
  linked_list a, b;
  node *p;
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
    case 1: {
      std::cout << "Vrednost: ";
      std::cin >> num1;
      if (a.search(num1))
        std::cout << "Podatek obstaja" << std::endl;
      else
        std::cout << "Podatek ne obstaja" << std::endl;
      break;
    }
    case 2:
      std::cout << "Vrednost: ";
      std::cin >> num1;
      a.add_node_head(num1);
      break;
    case 3:
      std::cout << "Vrednost 1: ";
      std::cin >> num1;
      std::cout << "Vrednost 2: ";
      std::cin >> num2;
      p = a.search(num2);
      a.add_node_after(num1, p);
      break;
    case 4:
      std::cout << "Vrednost: ";
      std::cin >> num1;
      a.add_node_tail(num1);
      break;
    case 5:
      std::cout << "Vrednost: ";
      std::cin >> num1;
      p = a.search(num1);
      a.delete_node(p);
      break;
    case 6:
      a.display();
      break;
    case 7:
      a.rdisplay();
      break;
    case 8: {
      std::cout << "Vrednost: ";
      std::cin >> num1;
      start = std::chrono::system_clock::now();
      for (int i = 0; i < num1; i++) {
        b.add_node_head(i + 1);
      }
      end = std::chrono::system_clock::now();
      elapsed_seconds = end - start;
      end_time = std::chrono::system_clock::to_time_t(end);
      std::cout << "Finished computation at " << std::ctime(&end_time)
                << "elapsed time: " << elapsed_seconds.count() << "s"
                << std::endl;
      start = std::chrono::system_clock::now();
      b.sum_head_to_tail();
      end = std::chrono::system_clock::now();
      elapsed_seconds = end - start;
      end_time = std::chrono::system_clock::to_time_t(end);
      std::cout << "Finished computation at " << std::ctime(&end_time)
                << "elapsed time: " << elapsed_seconds.count() << "s"
                << std::endl;
      std::cout << "Vrednost: ";
      std::cin >> num1;
      start = std::chrono::system_clock::now();
      int *ptr = add_to_head_array(num1);
      end = std::chrono::system_clock::now();
      for (int i = 0; i < num1; i++) {
        std::cout << *(ptr + i) << " ";
      }
      std::cout << std::endl;
      elapsed_seconds = end - start;
      end_time = std::chrono::system_clock::to_time_t(end);
      std::cout << "Finished computation at " << std::ctime(&end_time)
                << "elapsed time: " << elapsed_seconds.count() << "s"
                << std::endl;
      long long vsota = 0;
      start = std::chrono::system_clock::now();
      for (int i = 0; i < num1; i++) {
        vsota += *(ptr + i);
      }
      end = std::chrono::system_clock::now();
      std::cout << vsota << std::endl;
      elapsed_seconds = end - start;
      end_time = std::chrono::system_clock::to_time_t(end);
      std::cout << "Finished computation at " << std::ctime(&end_time)
                << "elapsed time: " << elapsed_seconds.count() << "s"
                << std::endl;
      std::cout << "Vrednost: ";
      std::cin >> num1;
      int array[num1];
      start = std::chrono::system_clock::now();
      for (int i = 0; i < num1; i++) {
        array[i] = i + 1;
      }
      end = std::chrono::system_clock::now();
      for (int i = 0; i < num1; i++) {
        std::cout << array[i] << " ";
      }
      elapsed_seconds = end - start;
      end_time = std::chrono::system_clock::to_time_t(end);
      std::cout << "Finished computation at " << std::ctime(&end_time)
                << "elapsed time: " << elapsed_seconds.count() << "s"
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