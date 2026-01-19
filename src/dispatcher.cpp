#include "dispatcher.hpp"
#include "getInternMap.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void dispatcher(const std::vector<std::string> &tokens) {
  if (tokens.empty()) {
    return;
  }
  const auto &InternMap = getInternMap();
  auto it = InternMap.find(tokens[0]);

  if (it != InternMap.end()) {
    it->second(tokens);
  } else {
    std::cout << "MiniShell-> Command not found: " << tokens[0] << std::endl;
  }
}
