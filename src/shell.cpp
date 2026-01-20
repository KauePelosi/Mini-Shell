#include "shell.hpp"
#include "dispatcher.hpp"
#include "tokenize.hpp"
#include <iostream>
#include <limits.h>
#include <linux/limits.h>
#include <string>
#include <unistd.h>

void shell() {
  std::string input{};
  char cwd[PATH_MAX];

  while (true) {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      std::cout << "MiniShell in " << cwd << "-> " << std::flush;
    } else {
      perror("getcwd() error");
      std::cout << "MiniShell-> " << std::flush;
    }
    if (!std::getline(std::cin, input)) {
      break;
    }

    auto tokens = tokenize(input);
    if (!tokens.empty()) {
      dispatcher(tokens);
    }
  }
}
