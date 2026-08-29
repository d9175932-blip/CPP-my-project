#ifndef CS503P_ARGS_H
#define CS503P_ARGS_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

class Args {
public:
  Args(int argc, char* argv[]) : i(1), argc(argc), argv(argv) {}

  // true if at least one more argument remains
  bool has() const {
    return i < argc;
  }

  // the next argument as text (spaces of a quoted argument intact)
  std::string next() {
    check();
    return argv[i++];
  }

  // the next argument converted to T; next<std::string>() preserves the
  // complete argument, including spaces kept together by shell quotes
  template <typename T>
  T next() {
    check();
    if constexpr (std::is_same_v<T, std::string>) {
      return argv[i++];
    } else {
      std::istringstream ss(argv[i]);
      T value;
      if (!(ss >> value)) {
        std::cerr << "bad argument: " << argv[i] << "\n";
        std::exit(1);
      }
      i++;
      return value;
    }
  }

private:
  void check() const {
    if (i >= argc) {
      std::cerr << "missing argument\n";
      std::exit(1);
    }
  }

  int i;
  int argc;
  char** argv;
};
