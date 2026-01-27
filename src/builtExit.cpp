#include <iostream>
#include <string>
#include <vector>

int builtExit(const std::vector<std::string> &tokens) {
  int status = 0;
  if (tokens.size() > 1) {
    try {
      status = std::stoi(tokens[1]);
    } catch (...) {
      std::cerr << "exit: numeric argument required\n";
    }
  }
  std::cout << "exit" << std::endl;
  std::exit(status);
  return status;
}
