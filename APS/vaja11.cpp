#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

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
        for(int i = 0; i < d; i++){
          arr[i] = 0;
        }
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
    std::stack<Path *> N;
    int **C;
    int nodes;
    Path *head;

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
      int index = 0;
      Path *ptr = nullptr;
      for (int i = 1; i < nodes; i++){
        int cost = C[i][index];
        if(cost > 0){
          if(ptr != nullptr){
            ptr->next = new Path(i, index, cost, nodes);
            ptr = ptr->next;
          }else{
            head = new Path(i, index, cost, nodes);
            ptr = head;
          }
        }
      }
      N.push(head);
      for (int k = 1; k < nodes-1; k++){
        head = nullptr;
        ptr = head;
        for (int i = 1; i < nodes; i++){
          Path *pp = N.top();
          while(pp != nullptr){
            if(pp->fromNode != i){
              int cost = C[i][pp->fromNode];
              if(cost > 0){
                if(!pp->arr[i]){
                  Path *tmp = new Path(i, pp->fromNode, cost+pp->cost, nodes);
                  for(int l = 0; l < nodes; l++){
                    tmp->arr[l] = pp->arr[l];
                  }
                  tmp->arr[pp->fromNode] = 1;
                  if(!purgePaths(tmp)){
                    if(head == nullptr){
                      head = tmp;
                      ptr = head;
                    }else{
                      ptr->next = tmp;
                      ptr = ptr->next;
                    }
                  }
                }
              }
            }
            pp = pp->next;
          }
        }
        N.push(head);
      }
      head = nullptr;
      ptr = head;
      Path *pp = N.top();
      while(pp != nullptr){
        if(pp->fromNode != index){
          int cost = C[index][pp->fromNode];
          if(cost > 0){
            if(!pp->arr[index]){
              Path *tmp = new Path(index, pp->fromNode, cost+pp->cost, nodes);
              for(int ind = 0; ind < nodes; ind++){
                tmp->arr[ind] = pp->arr[ind];
              }
              tmp->arr[pp->fromNode] = 1;
              if(!purgePaths(tmp)){
                if(head == nullptr){
                  head = tmp;
                  ptr = head;
                }else{
                  ptr->next = tmp;
                  ptr = ptr->next;
                }
              }
            }
          }
        }
        pp = pp->next;
      }
      N.push(head);
      if(head != nullptr) {
        std::cout << "Cost: " << head->cost << std::endl;
      } else {
        std::cout << "No cycle found." << std::endl;
      }
    }

    bool purgePaths(Path *pp) {
      Path *tmp = head;
      bool chk = false;
      while(tmp != nullptr) {
        if(pp->fromNode == tmp->fromNode) {
          bool diff = false;
          for(int i = 0; i < nodes; i++) {
            if(tmp->arr[i] != pp->arr[i]) {
              diff = true;
              break;
            }
          }
          if(!diff) {
            chk = true;
            if(tmp->cost > pp->cost) {
              tmp->fromNode = pp->fromNode;
              tmp->toNode = pp->toNode;
              tmp->cost = pp->cost;
              for(int i = 0; i < nodes; i++) {
                tmp->arr[i] = pp->arr[i];
              }
            }
          }
        }
        tmp = tmp->next;
      }
      return chk;
    }

    void levelsPrint(){
      std::stack<Path *> tmp = N;
      int num = tmp.size();
      while(!tmp.empty()){
        Path *p = tmp.top();
        std::cout << "====" << num << "====:" << std::endl << p->toString();
        tmp.pop();
        num--;
      }
    }

    void reconstructPath() {
      std::stack<Path*> tmpN = N;
      Path* pp = tmpN.top();
      tmpN.pop();
      int begin = pp->fromNode;
      std::cout << "Total cost: " << pp->cost << std::endl;
      std::cout << begin+1 << " => " << pp->toNode+1 << " => ";
      while(!tmpN.empty()) {
        Path *tmp = tmpN.top();
        while(nullptr != tmp) {
          bool* arr = new bool[nodes];
          for(int i = 0; i < nodes; i++) {
            arr[i] = pp->arr[i];
          }
          arr[pp->toNode] = false;
          if(tmp->fromNode == pp->toNode) {
            bool diff = false;
            for(int i = 0; i < nodes; i++) {
              if(arr[i] != tmp->arr[i]) {
                diff = true;
                break;
              }
            }
            if(!diff) {
              *pp = *tmp;
              if(pp->toNode != begin) {
                std::cout << pp->toNode+1 << " => ";
              }
              break;
            }
          }
          delete[] arr;
          tmp = tmp->next;
        }
        tmpN.pop();
      }

      std::cout << begin+1 << std::endl;
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
      if(N.size() > 0){
        while(!N.empty()){
          delete N.top();
          N.pop();
        }
        for (int i = 0; i < nodes; i++) {
          delete[] C[i];
        }
        delete[] C;
      }
    }

    ~Graph() {
        while(!N.empty()){
          delete N.top();
          N.pop();
        }
        for (int i = 0; i < nodes; i++) {
          delete[] C[i];
        }
        delete[] C;
    }
};

void menu() {
  std::cout << "======================================" << std::endl;
  std::cout << "================ MENU ================" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << "1) Read graph from file" << std::endl;
  std::cout << "2) Run travelers salesmen alorithm" << std::endl;
  std::cout << "3) Print levels" << std::endl;
  std::cout << "4) Path reconstuction" << std::endl;
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
  bool check1 = false, check2 = false;
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
                check1 = true;
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
      case 2:  {
                 if (check1) {
                   check2 = true;
                   start = std::chrono::system_clock::now();
                   G.findCycle();
                   end = std::chrono::system_clock::now();
                   std::cout << "Elapsed time[µs]: "
                     << std::chrono::duration_cast<std::chrono::microseconds>(
                         end - start)
                     .count()
                     << std::endl;
                 } else {
                   std::cout << "Read graph from file."
                     << std::endl;
                 }
                 break;
               }
      case 3:{
               if(check1 && check2){
                 G.levelsPrint();
               } else {
                 std::cout << "Read graph from file and execute algorithm."
                   << std::endl;
               }
               break;
             }
      case 4: {
                if(check1 && check2){
                  G.reconstructPath();
                } else {
                  std::cout << "Read graph from file and execute algorithm."
                    << std::endl;
                }
                break;
              }
      case 5: {
                if(check1 && check2){
                  G.displayMatrix();
                }else{
                  std::cout << "Read graph from file and execute algorithm." << std::endl;
                }
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
