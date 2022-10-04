#include <iostream>

struct node {
  int data;
  node *parent, *left, *right;
};

void add_node(node *&head, int k) {
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
        std::cout << "Napaka" << std::endl;
        return;
      }
    }
  }
  node *c = new node();
  c->data = k;
  c->parent = b;

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
    std::cout << a->data << " ";
    display(a->right);
  }
}

void display_link(node *a) {
  if (a->left != NULL) {
    std::cout << a->data << "->" << a->left->data << " ";
    display_link(a->left);
  }

  if (a->right != NULL) {
    std::cout << a->data << "->" << a->right->data << " ";
    display_link(a->right);
  }
}

void menu() {
  std::cout << "======================================" << std::endl;
  std::cout << "================ MENU ================" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "1) Vnos podatka" << std::endl;
  std::cout << "2) Urejen izpis vrednosti" << std::endl;
  std::cout << "3) Izpis povezav" << std::endl;
  std::cout << "4) Iskanje podatka" << std::endl;
  std::cout << "5) Poisci minimum in maksimum" << std::endl;
  std::cout << "6) Poisci predhodnika in naslednika" << std::endl;
  std::cout << "7) Brisanje podatka" << std::endl;
  std::cout << "0) Konec" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "Select: ";
}

int main() {
  bool running = true;
  int selection, num1, num2;
  node *head = nullptr;
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
    case 1:
      std::cout << "Vrednost: ";
      std::cin >> num1;
      add_node(head, num1);
      break;
    case 2:
      display(head);
      break;
    case 3:
      display_link(head);
      break;
    case 4:
      std::cout << "Vrednost: ";
      std::cin >> num1;
      if (search_node(head, num1))
        std::cout << "Podatek obstaja" << std::endl;
      else
        std::cout << "Podatek ne obstaja" << std::endl;
      break;
    case 5: {
      node *a = minimum_node(head);
      node *b = maximum_node(head);
      if (a || b) {
        std::cout << a->data << std::endl;
        std::cout << b->data << std::endl;
      } else
        std::cout << "Podatek ne obstaja" << std::endl;
      break;
    }
    case 6: {
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
    case 7: {
      std::cout << "Vrednost: ";
      std::cin >> num1;
      node *a = search_node(head, num1);
      if (a)
        delete_node(head, a);
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