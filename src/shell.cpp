#include <iostream>
#include <string>

int main() {
  std::string entrada;
  while (true) {
    std::cout << "MiniShell-> " << std::flush;

    if (!std::getline(std::cin, entrada)) {
      break;
    }
    if (entrada.empty()) {
      continue;
    }
  }
  return 0;
}
