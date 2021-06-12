#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

int randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

class Graph {
  private:
    struct Path {
      int fromNode;
      int toNode;
      int cost;
      bool *arr; //S
      Path *next;
      Path(int a, int b, int c, int d){
        fromNode = a;
        toNode = b;
        cost = c;
        arr = new bool[d];
        next = nullptr;
      }
      std::string toString() {
        std::stringstream ss;
        Path *head = this;
        do{
          ss << head->fromNode+1 << " => " << head->toNode+1 << ": " << head->cost << std::endl;
          head = head->next;
        }while(head != nullptr);
        return ss.str();
      }
    };
    std::vector<Path *> P;
    int **C;
    int nodes;

  public:
    Graph() {}

    void createNeighbours(int a) {
      nodes = a;
      C = new int *[a];
      for (int i = 0; i < a; i++)
        C[i] = new int[a];
    }

    void addPrice(int a, int b, int c) { C[a][b] = c; }

    void findCycle() {
      std::stack<Path*> N;
      Path *head = nullptr;
      for (int i = 1; i < nodes; i++){
        Path *tmp = new Path(i, 0, C[i][0], nodes);
        tmp->next = head;
        head = tmp;
      }
      for (int k = 1; k < nodes-1; k++){
        Path *head = nullptr;
        for(int i = 1; i < nodes; i++){
          Path *pp = N.top();
          do{
            if(pp->arr[i]){
              int price = C[i][k] + pp->cost;
              Path *tmp = new Path(k, i, price, nodes);
              tmp->next = head;
              head = tmp;
            }
            pp = pp->next;
          }while(pp != nullptr);
        }
        N.push(head);
      }
      int n = N.size();
      while(!N.empty()){
        Path *pp = N.top();
        std::cout << "Nivo " << n-N.size()+1 << ".:" << std::endl;
        do{
          std::cout << pp->toString();
          pp = pp->next;
        }while(pp != nullptr);
        N.pop();
      }
      //N.push(head);
    }

    /* void findPath(node *v1, int &cost) {
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
       }*/

    void displayMatrix() {
      for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
          std::cout << (j > 0 ? ", " : "") << C[i][j];
        }
        std::cout << std::endl;
      }
    }

    void clear(){
      if(P.size() > 0){
        for (int i = 0; i < nodes; i++) {
          delete P[i];
          delete[] C[i];
        }
        P.clear();
        delete[] C;
      }
    }

    ~Graph() {
      for (int i = 0; i < nodes; i++) {
        delete P[i];
        delete[] C[i];
      }
      P.clear();
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
  do {
    menu();
    std::cin >> selection;
    switch (selection) {
      case 1: {
                std::cout << "Choose file [1]-graf11_1.txt, [2]-graf11_2.txt: ";
                std::cin >> num1;
                if (num1 != 1 && num1 != 2) {
                  std::cout << "Wrong file" << std::endl;
                  break;
                }
                std::ifstream f("graf11_" + std::to_string(num1) + ".txt");
                f >> nodes;
                int *len = new int[nodes];
                G.clear();
                G.createNeighbours(nodes);
                check = true;
                for (int i = 0; i < nodes; i++) {
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
                  start = std::chrono::system_clock::now();
                  G.findCycle();
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
                /*if (check) {
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
                break;*/
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
