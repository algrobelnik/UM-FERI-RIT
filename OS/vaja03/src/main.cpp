#include "mymalloc.h"
#include <assert.h>
#include <iostream>
#include <string.h>

#define SSIZE sizeof(sector)

using namespace std;

/*int main() {
  aleks::setLogDebug(true);
  void *addr1 = aleks::mymalloc(25000 - SSIZE - 4);
  assert(aleks::getSector(addr1)->size == 25000 - SSIZE);

  void *addr2 = aleks::mymalloc(1);
  assert(addr2 == nullptr);

  aleks::myfree(addr1);
  assert(aleks::getHead()->size == 25000 - SSIZE);
  return 0;
}*/

int main() {
  void *addr = aleks::mymalloc(100);
  strncpy((char *)addr, "TESTTEST1", 10);
  void *addr2 = aleks::mymalloc(100);
  strncpy((char *)addr2, "NEKAJNEKAJ", 11);

  sector *sec = aleks::getSector(addr);
  sector *sec2 = aleks::getSector(addr2);
  cout << sec->toString() << endl;
  cout << sec2->toString() << endl;

  aleks::myfree(addr2);
  aleks::myfree(addr);
}
