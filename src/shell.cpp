#include "shell.hpp"
#include "dispatcher.hpp"
#include "printCwd.hpp"
#include "tokenize.hpp"
#include <iostream>
#include <limits.h>
#include <string>
#include <unistd.h>

void shell() {
  std::string input{};
  char cwd[PATH_MAX];
  int status{};
  while (true) {
    printCwd();

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
