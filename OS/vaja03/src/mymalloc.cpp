#include "mymalloc.h"

#include <assert.h>
#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZE 500   // log size
#define MSIZE 25000 // memory size

#define SSIZE sizeof(sector)
#define MFREE (0x0 << 7)      // free memory
#define MALLOCATED (0x1 << 7) // memory allocated

void *head = nullptr;
bool init = false;
bool debug = false;

// TODO
// 12. fix validate if not allready done

std::string sector::toString() const {
  std::stringstream ss;
  ss << this << "-> PrevSecIndex: " << this->prev << ", Size: " << this->size
     << ", Free: " << (this->free ? "Yes" : "No")
     << ", DataBufferStart: " << (char *)this + SSIZE
     << ", Data: " << (this->free ? "Empty" : (char *)this + SSIZE);
  return ss.str();
}

void *aleks::mymalloc(unsigned short size) {
  std::cout << "========== " << __func__ << " called with " << size
            << " ==========" << std::endl;
  // initialise
  if (!init) {
    // Filling head with zeros to avoid errors
    std::cout << "Initializing memory for the first time " << std::endl;
    head = malloc(MSIZE);
    memset(head, 0, MSIZE);
    std::cout << "Buffer location " << head << std::endl;

    // Add head to first sector
    sector *curr = (sector *)head;
    curr->free = true;
    curr->size = MSIZE - SSIZE;
    curr->prev = nullptr;
    init = true;
  }

  // loop util sector with enough space
  sector *curr = (sector *)head;
  while ((char *)curr - (char *)head < MSIZE) {
    std::cout << "Current sector" << curr->toString() << std::endl;

    if (curr->free && curr->size >= size) {
      if ((char *)curr + SSIZE * 2 + size - (char *)head < MSIZE) {
        sector *next = (sector *)((char *)curr + SSIZE + size);
        next->free = true;
        next->size = curr->size - SSIZE - size;
        next->prev = curr;
        std::cout << "New sector " << next->toString() << std::endl;
      } else {
        std::cout << "Allocating a size of " << curr->size << " instead of "
                  << size << ". Reason: BufferWaste" << std::endl;
        size = curr->size;
      }

      curr->free = false;
      curr->size = size;
      std::cout << "Returning sector " << curr->toString() << std::endl;
      return (void *)((char *)curr + SSIZE);
    }
    curr = (sector *)((char *)curr + SSIZE + curr->size);
    std::cout << "Loop: sector " << curr << std::endl;
  }
  std::cout << "Sector out of range: " << curr << std::endl;
  return 0;
}

void aleks::myfree(void *addr) {
  std::cout << "========== " << __func__ << " called with " << addr
            << " ==========" << std::endl;
  sector *sec = (sector *)((char *)addr - SSIZE);
  if (!checkSector(sec)) {
    std::cout << "Provided address " << addr << " doesn't point to valid sector"
              << std::endl;
    assert(false);
  }
  std::cout << "Freeing sector " << sec->toString() << std::endl;
  sec->free = true;

  // merge surrounding sectors if posible
  if (sec->prev != nullptr) {
    std::cout << "Left sector " << sec->prev->toString() << std::endl;
    std::cout << "Freeing sector " << sec->toString() << std::endl;
    if (sec->prev->free) {
      std::cout << "Meging with left sector " << sec->prev << std::endl;
      sec->prev->size += sec->size + SSIZE;
      memset((char *)sec, 0, sec->size + SSIZE);
      sec = sec->prev;
      std::cout << "Merged sector " << sec << std::endl;
    } else {
      std::cout << "Left sector is not empty" << std::endl;
    }
  } else {
    std::cout << "There is no left sector" << std::endl;
  }

  if (((char *)sec) + SSIZE + sec->size < (char *)head + MSIZE - 1) {
    sector *next = (sector *)(((char *)sec) + SSIZE + sec->size);
    std::cout << "Right sector " << next->toString() << std::endl;
    std::cout << "Updating right sector" << std::endl;
    next->prev = sec;
    if (next->free) {
      std::cout << "Merging with the right sector" << std::endl;
      sector *right = (sector *)(((char *)next) + SSIZE + next->size);
      sec->size += next->size + SSIZE;
      sec->free = true;
      memset((char *)next, 0, next->size + SSIZE);
      std::cout << "Merged sector " << sec->toString() << std::endl;
      if (checkSector(right)) {
        std::cout << "Updating right sector of next sector" << std::endl;
        std::cout << "Right of next sector " << right->toString() << std::endl;
        right->prev = sec;
        std::cout << "Updated right of next sector " << right->toString()
                  << std::endl;
      }
    } else {
      std::cout << "Right sector is not empty" << std::endl;
    }
  } else {
    std::cout << "There is no right sector" << std::endl;
  }

  std::cout << "Sector freed " << sec->toString() << std::endl;
}

sector *aleks::getSector(void *addr) {
  return (sector *)((char *)addr - SSIZE);
}

sector *aleks::getHead() { return (sector *)head; }

bool aleks::checkSector(sector *sec) {
  if ((char *)sec - (char *)head > MSIZE) {
    return false;
  }
  return true;
}
