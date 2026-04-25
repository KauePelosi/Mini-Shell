#include "utils/hasRedirection.hpp"
#include <algorithm>
#include <string>
#include <vector>

bool hasRedirection(const std::vector<std::string> &tokens) {
  std::string redirection = ">";

  auto it = std::find(tokens.begin(), tokens.end(), redirection);

  if (it == tokens.end()) {
    return false;
  }
  return true;
}
