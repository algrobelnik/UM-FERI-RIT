#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

struct el {
  std::string name;
  el *next;
};

class linked_list {
private:
  el *head, *tail;

public:
  linked_list() {
    head = NULL;
    tail = NULL;
  }

  void add_el(std::string d) {
    el *tmp = new el;
    tmp->name = d;
    tmp->next = NULL;

    if (head == NULL) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tail->next;
    }
  }

	void delete_el() {
    el *tmp = head;
    head = head->next;
    if (tail == tmp)
      tail == NULL;
    while (tmp != NULL) {
      tmp = tmp->next;
			delete tmp;
    }
  }

  void display_el() {
    struct el *tmp;
    tmp = head;
    while (tmp != NULL) {
      std::cout << tmp->name << " ";
      tmp = tmp->next;
    }
  }
};

struct node {
  int data;
  node *parent, *left, *right;
  linked_list list;
};

void add_node(node *&head, int k, std::string name) {
  node *a, *b;
  b = NULL;
  a = head;

  while (a != NULL) {
    b = a;
    if (k < a->data) {
      a = a->left;
    } else {
      if (k > a->data) {
        a = a->right;
      } else {
        a->list.add_el(name);
        return;
      }
    }
  }
  node *c = new node();
  c->data = k;
  c->parent = b;
	linked_list ls;
	c->list = ls;
	c->list.add_el(name);

  if (b == NULL) {
    head = c;
  } else {
    if (c->data < b->data) {
      b->left = c;
    } else {
      b->right = c;
    }
  }
}

node *minimum_node(node *a) {
  while (a->left != NULL) {
    a = a->left;
  }
  return a;
}

node *maximum_node(node *a) {
  while (a->right != NULL) {
    a = a->right;
  }
  return a;
}

node *next_node(node *a) {
  node *b;
  if (a->right != NULL)
    return minimum_node(a->right);

  b = a->parent;
  while (b != NULL && a == b->right) {
    a = b;
    b = b->parent;
  }

  return b;
}

node *prev_node(node *a) {
  node *b;
  if (a->left != NULL)
    return maximum_node(a->left);

  b = a->parent;
  while (b != NULL && a == b->left) {
    a = b;
    b = b->parent;
  }

  return b;
}

void delete_node(node *&head, node *b) {
  if (head->left == NULL && head->right == NULL) {
    std::cout << "Cannot delete head" << std::endl;
    return;
  }
  node *c, *d;
  if (b->left == NULL || b->right == NULL)
    c = b;
  else
    c = next_node(b);
  if (c->left != NULL)
    d = c->left;
  else
    d = c->right;
  if (d != NULL)
    d->parent = c->parent;
  if (c->parent == NULL) {
    head = d;
  } else {
    if (c == c->parent->left)
      c->parent->left = d;
    else
      c->parent->right = d;
  }
  if (b != c)
    b->data = c->data;
  delete c;
}

node *search_node(node *a, int k) {
  if (a == NULL || a->data == k) {
    return a;
  } else {
    if (k < a->data) {
      return search_node(a->left, k);
    } else {
      return search_node(a->right, k);
    }
  }
}

void display(node *a) {
  if (a != NULL) {
    display(a->left);
		std::cout << a->data << ": ";
		a->list.display_el();
		std::cout << std::endl;
    display(a->right);
  }
}

void menu() {
  std::cout << "======================================" << std::endl;
  std::cout << "================ MENU ================" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "1) Vnos filma" << std::endl;
  std::cout << "2) Urejen izpis filmov" << std::endl;
  std::cout << "3) Iskanje po datumu izdaje" << std::endl;
  std::cout << "4) Poisci minimum in maksimum" << std::endl;
  std::cout << "5) Poisci predhodnika in naslednika" << std::endl;
  std::cout << "6) Brisi datum" << std::endl;
  std::cout << "7) Nalaganje filmov iz datoteke" << std::endl;
  std::cout << "0) Konec" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "Select: ";
}

int main() {
	std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  std::time_t end_time;
  bool running = true;
  int selection, num1, num2;
  std::string str1;
  node *head = nullptr;
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
    case 1:
      std::cout << "Vrednost: ";
      std::cin >> num1;
			std::cout << "Vrednost: ";
      std::cin >> str1;
      add_node(head, num1, str1);
      break;
    case 2:
      display(head);
      break;
    case 3:{
      std::cout << "Vrednost: ";
      std::cin >> num1;
			start = std::chrono::system_clock::now();
      node *a = search_node(head, num1);
      end = std::chrono::system_clock::now();
      elapsed_seconds = end - start;
      end_time = std::chrono::system_clock::to_time_t(end);
      std::cout << "Elapsed time: " << elapsed_seconds.count() << "s"
                << std::endl;
      if (a){
				a->list.display_el();
        std::cout << "Podatek obstaja" << std::endl;
			}
      else
        std::cout << "Podatek ne obstaja" << std::endl;
      break;
		}
    case 4: {
      node *a = minimum_node(head);
      node *b = maximum_node(head);
      if (a || b) {
        std::cout << a->data << std::endl;
        std::cout << b->data << std::endl;
      } else
        std::cout << "Podatek ne obstaja" << std::endl;
      break;
    }
    case 5: {
      std::cout << "Vrednost: ";
      std::cin >> num1;
      node *a = next_node(search_node(head, num1));
      node *b = prev_node(search_node(head, num1));
      if (a && b) {
        std::cout << a->data << std::endl;
        std::cout << b->data << std::endl;
      } else
        std::cout << "Podatka ne obstajata" << std::endl;
      break;
    }
    case 6: {
      std::cout << "Vrednost: ";
      std::cin >> num1;
      node *a = search_node(head, num1);
      if (a){
				a->list.delete_el();
        delete_node(head, a);
			}
      break;
    }
    case 7: {
			std::ifstream in("IMDB_date_name_mini_sorted.list");
			int N;
			in >> N;
			start = std::chrono::system_clock::now();
			for(int i=0;i<N;i++){
				in >> num1;
				std::getline(in, str1, '\n');
				add_node(head, num1, str1);
				if(i%1000==0){
					std::cout << "*" << std::flush;
				}
			}
			end = std::chrono::system_clock::now();
			elapsed_seconds = end - start;
			end_time = std::chrono::system_clock::to_time_t(end);
			std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
			double vsota=0;
			int numbers[] = {19980000, 20080420, 20030212, 20130122, 19900103};
			for (int i = 0; i < 5; i++){
				start = std::chrono::system_clock::now();
				node *a = search_node(head, numbers[i]);
				end = std::chrono::system_clock::now();
				elapsed_seconds = end - start;
				end_time = std::chrono::system_clock::to_time_t(end);
				vsota += elapsed_seconds.count();
			}
      std::cout << "Elapsed time: " << vsota << "s" << std::endl;
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