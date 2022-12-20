#ifndef SYNC_QUEUE_H
#define SYNC_QUEUE_H
#include <condition_variable>
#include <list>
#include <mutex>
#include <iostream>

template <typename T> class SyncQueue {
public:
  bool finished;
  SyncQueue() { finished = false; }
  void insert(const T &data);
  void switchFinished();
  T read();
  std::list<T> queue;

private:
  SyncQueue(const SyncQueue &);
  SyncQueue &operator=(const SyncQueue &);
  std::mutex mtx;
  std::condition_variable cv;
};
template <typename T> void SyncQueue<T>::insert(const T &data) {
  std::unique_lock<std::mutex> lock(mtx);
  queue.push_back(data);
  cv.notify_one();
}
template <typename T> void SyncQueue<T>::switchFinished() {
  finished = !finished;
}
template <typename T> T SyncQueue<T>::read() {
  std::unique_lock<std::mutex> lock(mtx);
  while (queue.empty() && !finished) {
    cv.wait(lock);
  }
  if (queue.empty()) { 
    return T();
  }
  T res = queue.front();
  queue.pop_front();
  return res;
}
#endif // SYNC_QUEUE_H
