#include "shell.hpp"
#include "dispatcher.hpp"
#include "history.hpp"
#include "historyGlobal.hpp"
#include "printCwd.hpp"
#include "tokenize.hpp"
#include <iostream>
#include <limits.h>
#include <string>
#include <unistd.h>

void shell() {
  history.load();

  std::string input{};
  char cwd[PATH_MAX];
  int status{};

  while (true) {
    printCwd();

    if (!std::getline(std::cin, input)) {
      std::cout << "\n";
      break;
    }
    history.add(input);
    auto tokens = tokenize(input);
    if (!tokens.empty()) {
      status = dispatcher(tokens);
    }
  }
}
