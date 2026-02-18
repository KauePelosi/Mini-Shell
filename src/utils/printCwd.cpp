#include "utils/printCwd.hpp"
#include "config.hpp"
#include <iostream>
#include <limits.h>
#include <unistd.h>

void printCwd() {
  char cwd[PATH_MAX];

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    std::cout << shellName << " in " << cwd << "-> " << std::flush;
  } else {
    perror("getcwd() error");
    std::cout << shellName << "-> " << std::flush;
  }
}
