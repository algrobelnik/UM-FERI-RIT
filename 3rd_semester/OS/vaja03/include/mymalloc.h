#include <sstream>

struct sector {
  bool free;
  unsigned short size;
  sector *prev;

  std::string toString() const;
};

namespace aleks{
void *mymalloc(unsigned short size);
void myfree(void *addr);

sector *getSector(void *addr);
sector *getHead();

bool checkSector(sector *sec);
} // namespace aleks
