#ifndef WEAPONRY_SRC_ATOMQUE_H
#define WEAPONRY_SRC_ATOMQUE_H

#include <queue>
#include <mutex>

template <typename T, int N, typename CONTAINER = std::deque<T>>
class Atomque {
 public:
  Atomque() {
    que_.resize(N);
  }

  ~Atomque() = default;

 public:
  size_t size() {
    std::unique_lock<std::mutex> uqlck(mutex_);
    return que_.size();
  }

  void clear() {
    std::unique_lock<std::mutex> uqlck(mutex_);
    que_.clear();
  }

  bool empty() {
    std::unique_lock<std::mutex> uqlck(mutex_);
    return que_.empty();
  }

  T back() {
    
  }

  void push_back(const T& t) {
    
  }

  void pop_back() {
    
  }

  T front() {
    
  }

  void push_front(const T& t) {
    
  }

  void pop_front() {
    
  }

 private:
  std::mutex mutex_;
  CONTAINER que_;
};

#endif    // WEAPONRY_SRC_ATOMQUE_H
