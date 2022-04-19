#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

void print(const string &str, const vector<string> &vec) {
  cout << str;
  for (const auto &i : vec) {
    cout << i << endl;
  }
}

template <typename T> auto length(T const &value) {
  if constexpr (is_integral<T>::value) {
    return value;
  } else {
    return value.length();
  }
}

template <typename... Args> auto sum(Args... args) { return (args + ...); }

int main() {
  //Nested Namespaces
  /* BEFORE
    namespace Game {

      namespace Graphics {

        namespace Physics {

         class 2D {
            ..........
         };
        }
      }
    }
  */
  /* AFTER
   namespace Game::Graphics::Physics {
      class 2D {
      };
  }*/

  //Variable declaration in if and switch
  vector<string> vec{"abc", "xyz", "def", "smt"};
  if (const auto it = find(begin(vec), end(vec), "abc"); it != end(vec)) {
    *it = "$$$";
  }
  print("Vector: ", vec);

  //If constexpr statement
  int n{10};
  string s{"abc"};
  cout << "n = " << n << " and length = " << length(n) << endl;
  cout << "s = " << s << " and length = " << length(s) << endl << endl;

  map<string, string> fav_lang{
      {"John", "Java"}, {"Alex", "C++"}, {"Peter", "Python"}};
  auto result = fav_lang.insert({"Henry", "Golang"});
  for (const auto &[name, lang] : fav_lang) {
    cout << name << ":" << lang << endl;
  }
  cout << endl;

  //Folding Expressions
  cout << sum(11, 22, 33, 44, 55) << endl << endl;

  //Direct list initialization of enums
  enum byte : unsigned char {};
  byte b{0};          // OK
  //byte c{-1};         // ERROR
  byte d = byte{1};   // OK
  //byte e = byte{256}; // ERROR
  cout << (b ? "true" : "false") << " " << (d ? "true" : "false") << endl;

  return 0;
}
