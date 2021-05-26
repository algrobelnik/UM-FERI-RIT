#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

struct node {
  int prev;
  int len;
  int s;
  int i;
  std::string name;
};

class Graph {
private:
  std::vector<node *> V;
  int **C;
  int nodes;
  int index;

public:
  Graph() { index = 0; }

  void createNeighbours(int a) {
    nodes = a;
    C = new int *[a];
    for (int i = 0; i < a; i++)
      C[i] = new int[a];
  }

  void addNode(std::string a) {
    node *tmp = new node;
    tmp->name = a;
    tmp->i = index++;
    V.push_back(tmp);
  }

  void addPrice(int a, int b, int c) {
    C[a][b] = c;
    C[b][a] = c;
  }

  std::vector<node *> neighbours(node *a) {
    std::vector<node *> out;
    for (int i = 0; i < nodes; i++) {
      if (C[a->i][i] > 0)
        out.push_back(V[i]);
    }
    return out;
  }

  void depthSearch(node *v1, node *v2) {
    std::stack<node *> out;
    node *tmp;
    for (node *v : V) {
      v->s = 0;
      v->len = INT_MAX;
      v->prev = -1;
    }
    v1->s = 1;
    v1->len = 0;
    v1->prev = -1;
    out.push(v1);
    while (!out.empty()) {
      tmp = out.top();
      out.pop();
      if (v1 == v2) {
        return;
      }
      for (node *u : neighbours(tmp)) {
        if (u->s == 0) {
          u->s = 1;
          u->len = tmp->len + 1;
          u->prev = tmp->i;
          out.push(u);
        }
        tmp->s = 2;
      }
    }
  }

  void breadthSearch(node *v1, node *v2) {
    std::queue<node *> out;
    node *tmp;
    for (node *v : V) {
      v->s = 0;
      v->len = INT_MAX;
      v->prev = -1;
    }
    v1->s = 1;
    v1->len = 0;
    v1->prev = -1;
    out.push(v1);
    while (!out.empty()) {
      tmp = out.front();
      out.pop();
      if (v1 == v2) {
        return;
      }
      for (node *u : neighbours(tmp)) {
        if (u->s == 0) {
          u->s = 1;
          u->len = tmp->len + 1;
          u->prev = tmp->i;
          out.push(u);
        }
        tmp->s = 2;
      }
    }
  }

  node *search(std::string d) {
    for (int i = 0; i < nodes; i++) {
      if (V[i]->name == d) {
        return V[i];
      }
    }
    return NULL;
  }

  void findPath(node *v1, node *v2) {
    if (v1 == v2) {
      std::cout << "Path: " << v2->name << " ";
    } else {
      if (v2->prev == -1) {
        std::cout << "There is not path between " << v1->name << " and "
                  << v2->name << "!";
      } else {
        findPath(v1, V[v2->prev]);
        std::cout << v2->name << " ";
      }
    }
  }

  void displayNodes() {
    for (int i = 0; i < nodes; i++) {
      std::cout << V[i]->name << "[" << V[i]->i << "] " << V[i]->prev << " (" << V[i]->len << ") " << V[i]->s << std::endl;;
    }
    
  }

  void displayMatrix() {
    for (int i = 0; i < nodes; i++) {
      for (int j = 0; j < nodes; j++) {
        std::cout << (j > 0 ? ", " : "") << C[i][j];
      }
      std::cout << std::endl;
    }
  }

  ~Graph() {
    for (int i = 0; i < nodes; i++) {
      delete V[i];
      delete[] C[i];
    }
    V.clear();
    delete[] C;
  }
};

void menu() {
  std::cout << "======================================" << std::endl;
  std::cout << "================ MENU ================" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "1) Read graph from file" << std::endl;
  std::cout << "2) Depht-first search" << std::endl;
  std::cout << "3) Breadth-first search" << std::endl;
  std::cout << "4) Print all nodes" << std::endl;
  std::cout << "5) Print neighbours matrix" << std::endl;
  std::cout << "0) End" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "Select: ";
}

int main() {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  bool running = true;
  int nodes, conections;
  int selection, num1;
  std::string str1;
  int size;
  Graph G;
  bool check = false;
  node *n1, *n2;
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
    case 1: {
      std::cout << "Choose file [1]-graf.txt, [2]-grafBig.txt: ";
      std::cin >> num1;
      if (num1 == 1) {
        str1 = "graf.txt";
      } else if (num1 == 2) {
        str1 = "grafBig.txt";
      } else {
        std::cout << "Wrong file" << std::endl;
        break;
      }
      std::ifstream f(str1);
      f >> nodes;
      f >> conections;
      G.createNeighbours(nodes);
      check = true;
      std::vector<std::string> input;
      int v1, v2, price;
      for (int i = 0; i < conections; i++) {
        f >> v1 >> v2 >> price;
        std::vector<std::string>::iterator it1 = std::find(input.begin(), input.end(), std::to_string(v1));
        if(it1 == input.end()){
          input.push_back(std::to_string(v1));
          G.addNode(std::to_string(v1));
        }
        std::vector<std::string>::iterator it2 = std::find(input.begin(), input.end(), std::to_string(v2));
        if(it2 == input.end()){
          input.push_back(std::to_string(v2));
          G.addNode(std::to_string(v2));
        }
        G.addPrice(v1 - 1, v2 - 1, price);
      }
      break;
    }
    case 2: {
      std::cout << "Name of first node: ";
      std::cin >> str1;
      n1 = G.search(str1);
      if (n1 == NULL) {
        std::cout << "Cannot find first node" << std::endl;
        break;
      }
      std::cout << "Name of second node: ";
      std::cin >> str1;
      n2 = G.search(str1);
      if (n2 == NULL) {
        std::cout << "Cannot find second node" << std::endl;
        break;
      }
      start = std::chrono::system_clock::now();
      G.depthSearch(n1, n2);
      end = std::chrono::system_clock::now();
      std::cout << "Elapsed time[µs]: "
                << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                         start)
                       .count()
                << std::endl;
      G.findPath(n1, n2);
      std::cout << std::endl;
      std::cout << "Cost: " << n2->len << std::endl;
      break;
    }
    case 3: {
      std::cout << "Name of first node: ";
      std::cin >> str1;
      n1 = G.search(str1);
      if (n1 == NULL) {
        std::cout << "Cannot find first node" << std::endl;
        break;
      }
      std::cout << "Name of second node: ";
      std::cin >> str1;
      n2 = G.search(str1);
      if (n2 == NULL) {
        std::cout << "Cannot find second node" << std::endl;
        break;
      }
      start = std::chrono::system_clock::now();
      G.breadthSearch(n1, n2);
      end = std::chrono::system_clock::now();
      std::cout << "Elapsed time[µs]: "
                << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                         start)
                       .count()
                << std::endl;
      G.findPath(n1, n2);
      std::cout << std::endl;
      std::cout << "Cost: " << n2->len << std::endl;
      break;
    }
    case 4: {
      if (check) {
        G.displayNodes();
      } else {
        std::cout << "Generate neighbours first" << std::endl;
      }
      break;
    }
    case 5: {
      G.displayMatrix();
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