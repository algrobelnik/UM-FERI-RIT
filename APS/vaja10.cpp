#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

struct node {
  int prev;
  int len;
  int i;
};

class Graph {
private:
  std::vector<node *> V;
  int **C;
  int nodes;
  int index;
  int startIndex;

public:
  Graph() { index = 0; }

  void createNeighbours(int a) {
    nodes = a;
    C = new int *[a];
    for (int i = 0; i < a; i++)
      C[i] = new int[a];
  }

  void addNode() {
    node *tmp = new node;
    tmp->i = index++;
    V.push_back(tmp);
  }

  void addPrice(int a, int b, int c) { C[a][b] = c; }

  void Bellman_Ford(node *s) {
    startIndex = s->i;
    node *tmp;
    for (node *v : V) {
      v->len = 9999;
      v->prev = -1;
    }
    s->len = 0;
    for (int i = 0; i < V.size() - 1; i++) {
      for (node *u : V) {
        for (node *v : V) {
          if (u != v && u->len + C[u->i][v->i] < v->len) {
            v->len = u->len + C[u->i][v->i];
            v->prev = u->i;
          }
        }
      }
    }
    for (node *u : V) {
      for (node *v : V) {
        if (u != v && u->len + C[u->i][v->i] < v->len) {
          std::cout << "!!!!!ERROR!!!!!" << std::endl;
        }
      }
    }
  }

  node *search(int d) {
    for (int i = 0; i < nodes; i++) {
      if (V[i]->i == d) {
        return V[i];
      }
    }
    return NULL;
  }

  void findPath(node *v1, int &cost) {
    if (V[startIndex] == v1) {
      std::cout << "Path: " + std::to_string(v1->i + 1);
      return;
    }
    if (V[v1->prev] == NULL) {
      std::cout << "No path between " + std::to_string(V[startIndex]->i) +
                       " and " + std::to_string(v1->i + 1) + ".";
      return;
    } else {
      cost += C[v1->prev][v1->i];
      findPath(V[v1->prev], cost);
      std::cout << " => " << std::to_string(v1->i + 1);
    }
  }

  void displayNodes() {
    for (int i = 0; i < nodes; i++  ) {
      std::cout << "[" << V[i]->i + 1 << "] " << V[i]->prev << " (" << V[i]->len
                << ") " << std::endl;
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
  
  void clear(){
    index = 0;
    for (int i = 0; i < nodes; i++) {
      delete V[i];
      delete[] C[i];
    }
    V.clear();
    delete[] C;
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
  std::cout << "2) Generate random nodes" << std::endl;
  std::cout << "3) Run Bellman-Ford algorithm" << std::endl;
  std::cout << "4) Print shortest path" << std::endl;
  std::cout << "5) Print neighbours matrix" << std::endl;
  std::cout << "0) End" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "Select: ";
}

int main() {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  bool running = true;
  int nodes;
  int selection, num1;
  Graph G;
  bool check = false;
  node *n1, *n2;
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
    case 1: {
      std::cout << "Choose file [1]-graf1.txt, [2]-graf2.txt, [3]-graf3.txt: ";
      std::cin >> num1;
      if (num1 != 1 && num1 != 2 && num1 != 3) {
        std::cout << "Wrong file" << std::endl;
        break;
      }
      std::ifstream f("graf" + std::to_string(num1) + ".txt");
      // std::ifstream f("graf1.txt");
      f >> nodes;
      int *len = new int[nodes];
      G.clear();
      G.createNeighbours(nodes);
      check = true;
      for (int i = 0; i < nodes; i++) {
        G.addNode();
        for (int j = 0; j < nodes; j++) {
          f >> len[j];
          if (len[j] != 9999)
            G.addPrice(i, j, len[j]);
        }
      }
      delete[] len;
      break;
    }
    case 2: {
      std::cout << "Choose random graph nodes: ";
      std::cin >> num1;
      if (num1 > 1500)
        break;
      G.createNeighbours(num1);
      check = true;
      int p, q, price;
      for (int i = 0; i < num1; i++) {
        G.addNode();
        for (int j = 0; j < num1; j++) {
          p = j;
          q = j + 1;
          if (j + 1 > num1)
            q = 0;
          G.addPrice(p, q, randGen(0, num1));
        }
      }
      break;
    }
    case 3: {
      if (check) {
        std::cout << "Start node: ";
        std::cin >> num1;
        n1 = G.search(num1 - 1);
        if (n1 == NULL) {
          std::cout << "Cannot find start node" << std::endl;
          break;
        }
        start = std::chrono::system_clock::now();
        G.Bellman_Ford(n1);
        end = std::chrono::system_clock::now();
        std::cout << "Elapsed time[µs]: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(
                         end - start)
                         .count()
                  << std::endl;
      } else {
        std::cout << "Read graph from file or generate random nodes first."
                  << std::endl;
      }
      break;
    }
    case 4: {
      if (check) {
        std::cout << "Name of end node: ";
        std::cin >> num1;
        n1 = G.search(num1 - 1);
        if (n1 == NULL) {
          std::cout << "Cannot find end node" << std::endl;
          break;
        }
        int cost = 0;
        G.findPath(n1, cost);
        std::cout << std::endl << "Cost: " << cost << std::endl;
      } else {
        std::cout << "Read graph from file or generate random nodes first."
                  << std::endl;
      }
      break;
    }
    case 5: {
      G.displayNodes();
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