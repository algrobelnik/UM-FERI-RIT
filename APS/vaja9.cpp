#include <algorithm>
#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

struct conn {
  int p;
  int q;
  int cost;
  std::string toString() {
    std::stringstream ss;
    ss << "P: " << p << ", Q: " << q << ", C: " << cost;
    return ss.str();
  }
};

int split(std::vector<conn *> &vec, int a, int b) {
  int pivot = vec[a]->cost;
  int li = a;
  int ri = b;
  while (li < ri) {
    while (vec[li]->cost <= pivot && li < b)
      li++;
    while (vec[ri]->cost >= pivot && ri > a)
      ri--;
    if (li < ri)
      std::swap(vec[li], vec[ri]);
  }
  std::swap(vec[a], vec[ri]);
  return ri;
}

void quickSort(std::vector<conn *> &vec, int a, int b) {
  if (a < b) {
    int tmp;
    tmp = split(vec, a, b);
    quickSort(vec, a, tmp - 1);
    quickSort(vec, tmp + 1, b);
  }
}

class Graph {
private:
  std::vector<conn *> N;
  std::vector<conn *> res;
  std::vector<int> C;
  int nodes;

public:
  Graph() {}

  void setNodes(int n) {
    nodes = n;
    for (int i = 0; i < n; i++) {
      C.push_back(0);
    }
  }

  void addConn(int p, int q, int cost) {
    conn *tmp = new conn;
    tmp->p = p;
    tmp->q = q;
    tmp->cost = cost;
    N.push_back(tmp);
  }

  void kruskal() {
    quickSort(N, 0, N.size() - 1);
    int index = 1;
    for (conn *e : N) {
      if (C[e->p - 1] == C[e->q - 1] && C[e->p - 1] > 0 && C[e->q - 1] > 0) {
        continue;
      }
      if (C[e->p - 1] != C[e->q - 1] && C[e->p - 1] > 0 && C[e->q - 1] > 0) {
        res.push_back(e);
        if (C[e->p - 1] > C[e->q - 1]) {
          for (conn *tmp : N) {
            if (C[tmp->p - 1] == C[e->p - 1]) {
              C[tmp->p - 1] = C[e->q - 1];
              C[tmp->q - 1] = C[e->q - 1];
            }
          }
        } else {
          for (conn *tmp : N) {
            if (C[tmp->q - 1] == C[e->q - 1]) {
              C[tmp->p - 1] = C[e->p - 1];
              C[tmp->q - 1] = C[e->p - 1];
            }
          }
        }
      } else if ((C[e->p - 1] > 0 && C[e->q - 1] == 0) ||
                 (C[e->p - 1] == 0 && C[e->q - 1] > 0)) {
        res.push_back(e);
        if (C[e->q - 1] == 0) {
          C[e->q - 1] = C[e->p - 1];
        } else {
          C[e->p - 1] = C[e->q - 1];
        }
      } else if (C[e->p - 1] == 0 && C[e->q - 1] == 0) {
        res.push_back(e);
        C[e->p - 1] = index;
        C[e->q - 1] = index;
        index++;
      }
    }
  }

  conn *search(int d) {
    for (int i = 0; i < nodes; i++) {
      if (N[i]->p == d || N[i]->p == d) {
        return N[i];
      }
    }
    return NULL;
  }

  void display() {
    for (int i = 0; i < res.size(); i++) {
      std::cout << res[i]->toString() << std::endl;
    }
  }

  ~Graph() {
    for (int i = 0; i < nodes; i++) {
      delete N[i];
    }
    N.clear();
  }
};

void menu() {
  std::cout << "======================================" << std::endl;
  std::cout << "================ MENU ================" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "1) Read graph from file" << std::endl;
  std::cout << "2) Generate random graph" << std::endl;
  std::cout << "3) Kruskal algorithm" << std::endl;
  std::cout << "4) Print all nodes" << std::endl;
  std::cout << "0) End" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "Select: ";
}

int main() {
  srand(time(0));
  std::chrono::time_point<std::chrono::system_clock> start, end;
  bool running = true;
  int nodes, conections;
  int selection, num1;
  std::string str1;
  int size;
  Graph G;
  bool check = false;
  conn *n1, *n2;
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
    case 1: {
      std::cout << "Choose file [1]-graf_9.txt, [2]-grafRot.txt: ";
      std::cin >> num1;
      if (num1 == 1) {
        str1 = "graf_9.txt";
      } else if (num1 == 2) {
        str1 = "grafRot.txt";
      } else {
        std::cout << "Wrong file" << std::endl;
        break;
      }
      std::ifstream f(str1);
      f >> nodes;
      f >> conections;
      G.setNodes(nodes);
      int p, q, price;
      for (int i = 0; i < conections; i++) {
        f >> p >> q >> price;
        G.addConn(p, q, price);
      }
      break;
    }
    case 2: {
      std::cout << "Choose random graph nodes: ";
      std::cin >> num1;
      if(num1 > 1500) break;
      G.setNodes(num1);
      int p, q, price;
      for (int i = 0; i < num1; i++) {
        for (int j = 0; j < num1; j++){
          p = j+1;
          q = j+2;
          if(j+2 > num1+1) q = 1;
          price = randGen(0, num1);
          G.addConn(p, q, price);
        }
      }
      break;
    }
    case 3: {
      G.kruskal();
      break;
    }
    case 4: {
      G.display();
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