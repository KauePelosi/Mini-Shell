#include "dispatcher.hpp"
#include "externalCommands.hpp"
#include "getInternMap.hpp"
#include <string>
#include <unordered_map>
#include <vector>

int dispatcher(const std::vector<std::string> &tokens) {
  if (tokens.empty()) {
    return 0;
  }
  const auto &InternMap = getInternMap();
  auto it = InternMap.find(tokens[0]);

  if (it != InternMap.end()) {
    return it->second(tokens);
  } else {
    return externalCommands(tokens);
  }
}
