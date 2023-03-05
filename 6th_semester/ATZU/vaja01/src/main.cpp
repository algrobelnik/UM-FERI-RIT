#include <cmath>
#include <fstream>
#include <iostream>

int maxRobbers(int goldBars) {
  int max = -1;
  int logGoldBars = std::log(goldBars);
  for (int i = 2; i <= logGoldBars; i++) {
    int temp = goldBars;
    int modulus = temp % i;
    int j;
    for (j = 0; j < i && modulus == 1; j++) {
      temp -= (temp / i) + 1;
      modulus = temp % i;
    }
    if (modulus == 0 && j == i) {
      max = i;
    }
  }
  return max;
}

void readFile(std::string fileName) {
  std::ifstream file(fileName);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      int number = stoi(line);
      if (number < 0) {
        break;
      }
      int res = maxRobbers(number);
      std::cout << "st. zlatih palic: " << number << " - "
                << (res > 0 ? "st. roparjev: " + std::to_string(res)
                            : "ni resitve!")
                << std::endl;
    }
    file.close();
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Missing file as argument" << std::endl;
    return -1;
  }
  readFile(argv[1]);
  return 0;
}
