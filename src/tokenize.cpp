#include "tokenize.hpp"
#include <cctype>
#include <string>
#include <vector>

void addToken(std::vector<std::string> &tokens, std::string &temp) {
  tokens.push_back(std::move(temp));
  temp.clear();
}

std::vector<std::string> tokenize(const std::string &input) {
  std::vector<std::string> tokens;
  std::string temp;

  for (char c : input) {
    if (std::isspace(static_cast<unsigned char>(c))) {
      if (!temp.empty()) {
        addToken(tokens, temp);
      }
    } else {
      temp += c;
    }
  }

  if (!temp.empty()) {
    addToken(tokens, temp);
  }
  return tokens;
}
