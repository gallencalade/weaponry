#ifndef WEAPONRY_SRC_ATOMQUE_H
#define WEAPONRY_SRC_ATOMQUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T, int N = 1, typename CONTAINER = std::deque<T>>
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
    {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_any_.wait(lk, [this]{ return size() < N; });
    que_.push_back(t);
    }
    cond_var_any_.notify_all();
  }

  int try_push_back(const T& t) {
    if (mutex_.try_lock()) {
      if (N == que_.size()) {
        mutex_.unlock();
        return N;
      }

      que_.push_back(t);
      mutex_.unlock();
      cond_var_any_.notify_all();
      return 0;
    }

    return -1;
  }

  int push_back_until(const T& t, const std::chrono::milliseconds& ms) {
    {
    std::unique_lock<std::mutex> lk(mutex_);
    if (std::cv_status::timeout == cond_var_any_.wait_for(lk, ms)) {
      return -1;
    }

    if (N == que_.size()) {
      return N;
    }

    que_.push_back(t);
    }
    cond_var_any_.notify_all();

    return 0;
  }

  void squeese_back(const T& t) {
    std::unique_lock<std::mutex> lk(mutex_);
    if (N == que_.size()) {
      que_.pop_front();
    }

    que_.push_back(t);
  }

  int try_squeese_back(const T& t) {
    if (mutex_.try_lock()) {
      if (N == que_.size()) {
        que_.pop_front();
      }
      que_.push_back(t);
      mutex_.unlock();
      return 0;
    }

    return -1;
  }

  T front() {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_any_.wait(lk, !empty());
    return que_.front();
  }

  int try_front(T& t) {
    if (mutex_.try_lock()) {
      if (empty()) {
        mutex_.unlock();
        return N;
      }
      t = que_.front();
      mutex_.unlock();
      return 0;
    }

    return -1;
  }

  int front_util(T& t, const std::chrono::milliseconds& ms) {
    std::unique_lock<std::mutex> lk(mutex_);
    if (std::cv_status::timeout == cond_var_any_.wait_for(lk, ms)) {
      return -1;
    }
    if (empty()) {
      return N;
    }
    t = que_.front();

    return 0;
  }

  T pop_front() {
    T t;
    {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_any_.wait(lk, !empty());
    t = que_.front();
    que_.pop_front();
    }
    cond_var_any_.notify_all();

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
      cond_var_any_.notify_all();

      return 0;
    }

    return -1;
  }

  int pop_front_until(T& t, std::chrono::milliseconds& ms) {
    {
    std::unique_lock<std::mutex> lk(mutex_);
    if (std::cv_status::timeout == cond_var_any_.wait_for(lk, ms)) {
      return -1;
    }
    if (empty()) {
      return N;
    }
    t = que_.front();
    que_.pop_front();
    }
    cond_var_any_.notify_all();

    return 0;
  }

 private:
  std::mutex mutex_;
  std::condition_variable_any cond_var_any_;
  CONTAINER que_;
};

#endif    // WEAPONRY_SRC_ATOMQUE_H
