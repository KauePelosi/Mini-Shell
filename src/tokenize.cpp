#include "tokenize.hpp"
#include <cctype>
#include <string>
#include <vector>

std::vector<std::string> tokenize(const std::string &input) {
  std::vector<std::string> tokens;
  std::string temp;

  for (char c : input) {
    if (!std::isspace(static_cast<unsigned char>(c))) {
      temp += c;
    } else {
      if (!temp.empty()) {
        tokens.push_back(temp);
        temp.clear();
      }
    }
  }
  if (!temp.empty()) {
    tokens.push_back(temp);
  }
  return tokens;
}
