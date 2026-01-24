#include "shell.hpp"
#include "dispatcher.hpp"
#include "tokenize.hpp"
#include <iostream>
#include <limits.h>
#include <string>
#include <unistd.h>

void shell() {
  std::string input{};
  char cwd[PATH_MAX];
  int status{};
  std::string shellName = "MiniShell";
  while (true) {

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      std::cout << shellName << " in " << cwd << "-> " << std::flush;
    } else {
      perror("getcwd() error");
      std::cout << shellName << "-> " << std::flush;
    }
    if (!std::getline(std::cin, input)) {
      std::cout << "\n";
      break;
    }

    auto tokens = tokenize(input);
    if (!tokens.empty()) {
      status = dispatcher(tokens);
    }
  }
}
