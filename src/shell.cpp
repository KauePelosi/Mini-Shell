#include "shell.hpp"
#include "dispatcher.hpp"
#include "tokenize.hpp"
#include <iostream>
#include <string>

void shell() {
  std::string input{};
  while (true) {
    std::cout << "MiniShell-> " << std::flush;
    std::getline(std::cin, input);

    auto tokens = tokenize(input);
    dispatcher(tokens);
  }
}
