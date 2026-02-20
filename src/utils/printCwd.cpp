#include "utils/printCwd.hpp"
#include "config.hpp"
#include "core/shellContext.hpp"
#include <iostream>
#include <limits.h>
#include <unistd.h>

void printCwd(ShellContext &ctx) {
  char cwd[PATH_MAX];

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    std::cout << shellName << " in " << cwd << "-> " << std::flush;
    if (ctx.lastExitStatus != 0) {
      std::cout << "\033[31m✗\033[0m ";
    } else {
      std::cout << "\033[32m✓\033[0m ";
    }
  } else {
    perror("getcwd() error");
    std::cout << shellName << "-> " << std::flush;
  }
}
