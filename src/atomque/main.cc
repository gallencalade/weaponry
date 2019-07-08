#include <iostream>
#include <thread>

#include "atomque.h"

using weaponry::Atomque;

int main() {
  Atomque<int, 4> atomque;
  std::thread thd_size([&]{
    while (true) {
      std::cout << "thd_size: " << atomque.size() << std::endl;
    }
  });
  thd_size.detach();
  std::thread thd_empty([&]{
    while (true) {
      std::cout << "thd_empty: " << (atomque.empty() ? "empty" : "non-empty") << std::endl;
    }
  });
  thd_empty.detach();
  std::thread thd_push_back([&]{
    while(true) {
      atomque.push_back(1);
    }
  });
  thd_push_back.detach();
  std::thread thd_try_push_back([&]{
    while (true) {
      atomque.try_push_back(2);
    }
  });
  thd_try_push_back.detach();
  std::thread thd_push_back_until([&]{
    while (true) {
      atomque.push_back_until(3, std::chrono::milliseconds(1));
    }
  });
  thd_push_back_until.detach();
  std::thread thd_squeese_back([&]{
    while (true) {
      atomque.squeese_back(4);
    }
  });
  thd_squeese_back.detach();
  std::thread thd_try_squeese_back([&]{
    while (true) {
      atomque.try_squeese_back(5);
    }
  });
  thd_try_squeese_back.detach();
  std::thread thd_front([&]{
    while(true) {
      atomque.front();
    }
  });
  thd_front.detach();
  std::thread thd_try_front([&]{
    while(true) {
      int a = 0;
      atomque.try_front(a);
    }
  });
  thd_try_front.detach();
  std::thread thd_front_util([&]{
    while(true) {
      int a = 0;
      atomque.front_util(a, std::chrono::milliseconds(1));
    }
  });
  thd_front_util.detach();
  std::thread thd_pop_front([&]{
    while (true) {
      atomque.pop_front();
    }
  });
  thd_pop_front.detach();
  std::thread thd_try_pop_front([&]{
    while (true) {
      int a = 0;
      atomque.try_pop_front(a);
    }
  });
  thd_try_pop_front.detach();
  std::thread thd_pop_front_util([&]{
    while (true) {
      int a = 0;
      atomque.pop_front_until(a, std::chrono::milliseconds(1));
    }
  });
  thd_pop_front_util.join();
}
