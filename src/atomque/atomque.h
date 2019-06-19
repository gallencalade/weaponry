#ifndef WEAPONRY_SRC_ATOMQUE_H
#define WEAPONRY_SRC_ATOMQUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T, int N, typename CONTAINER = std::deque<T>>
class Atomque {
 public:
  Atomque() {
    que_.resize(N);
  }

  ~Atomque() = default;

 public:
  size_t size() {
    std::unique_lock<std::mutex> lk(mutex_);
    return que_.size();
  }

  void clear() {
    std::unique_lock<std::mutex> lk(mutex_);
    que_.clear();
  }

  bool empty() {
    std::unique_lock<std::mutex> lk(mutex_);
    return que_.empty();
  }

  void push_back(const T& t) {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_any_.wait(lk, [this]{ return size() < N; });
    que_.push_back(t);
  }

  int try_push_back(const T& t) {
    if (mutex_.try_lock()) {
      if (que_.size() < N) {
        que_.push_back(t);
        mutex_.unlock();
        return 0;
      }
      mutex_.unlock();
      return N;
    }

    return -1;
  }

  int push_back_until(const T& t, const std::chrono::milliseconds& ms) {
    std::unique_lock<std::mutex> lk(mutex_);
    if (std::cv_status::timeout == cond_var_any_.wait_for(lk, ms)) {
      return -1;
    }

    if (que_.size() < N) {
      que_.push_back(t);
      return 0;
    }

    return N;
  }

  T pop_back() {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_any_.wait(lk, !empty());
    T t = que_.back();
    que_.pop_back();

    return t;
  }

  int try_pop_back(T& t) {
    if (mutex_.try_lock()) {
      if (empty()) {
        mutex_.unlock();
        return N;
      }
      t = que_.back();
      que_.pop_back();
      mutex_.unlock();
      return 0;
    }

    return -1;
  }

  int pop_back_until(T& t, const std::chrono::milliseconds& ms) {
    std::unique_lock<std::mutex> lk(mutex_);
    if (std::cv_status::timeout == cond_var_any_.wait_for(lk, ms)) {
      return -1;
    }
    if (empty()) {
      return N;
    }
    t = que_.back();
    que_.pop_back();

    return 0;
  }

  void push_front(const T& t) {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_any_.wait(lk, [this]{ return size() < N; });
    que_.push_front(t);
  }

  int try_push_front(const T& t) {
    if (mutex_.try_lock()) {
      if (que_.size() < N) {
        que_.push_front(t);
        mutex_.unlock();
        return 0;
      }
      mutex_.unlock();
      return N;
    }

    return -1;
  }

  int push_front_until(const T& t, std::chrono::milliseconds& ms) {
    std::unique_lock<std::mutex> lk(mutex_);
    if (std::cv_status::timeout == cond_var_any_.wait_for(lk, ms)) {
      return -1;
    }

    if (que_.size() < N) {
      que_.push_front(t);
      return 0;
    }

    return N;
  }

  T pop_front() {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_any_.wait(lk, !empty());
    T t = que_.front();
    que_.pop_front();

    return t;
  }

  int try_pop_front(T& t) {
    if (mutex_.try_lock()) {
      if (empty()) {
        mutex_.unlock();
        return N;
      }
      t = que_.front();
      que_.pop_front();
      mutex_.unlock();
      return 0;
    }

    return -1;
  }

  int pop_front_until(T& t, std::chrono::milliseconds& ms) {
    std::unique_lock<std::mutex> lk(mutex_);
    if (std::cv_status::timeout == cond_var_any_.wait_for(lk, ms)) {
      return -1;
    }
    if (empty()) {
      return N;
    }
    t = que_.front();
    que_.pop_front();

    return 0;
  }

 private:
  std::mutex mutex_;
  std::condition_variable_any cond_var_any_;
  CONTAINER que_;
};

#endif    // WEAPONRY_SRC_ATOMQUE_H
