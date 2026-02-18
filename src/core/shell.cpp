#include "core/shell.hpp"
#include "core/dispatcher.hpp"
#include "core/tokenize.hpp"
#include "utils/history.hpp"
#include "utils/historyGlobal.hpp"
#include "utils/printCwd.hpp"
#include <iostream>
#include <limits.h>
#include <string>
#include <unistd.h>

void shell() {
  history.load();

  std::string input{};
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
