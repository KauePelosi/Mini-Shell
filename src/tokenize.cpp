#include "tokenize.hpp"
#include <cctype>
#include <string>
#include <vector>

std::vector<std::string> tokenize(const std::string &input) {
  std::vector<std::string> tokens;
  std::string temp;
  bool inQuotes = false;
  char quoteChar = '\0';

  for (char c : input) {
    if (inQuotes) {
      if (c == quoteChar) {
        inQuotes = false;
      } else {
        temp += c;
      }
    } else {
      if (c == '"' || c == '\'') {
        inQuotes = true;
        quoteChar = c;
      } else if (std::isspace(static_cast<unsigned char>(c))) {
        if (!temp.empty()) {
          tokens.push_back(temp);
          temp.clear();
        }
      } else {
        temp += c;
      }
    }
  }
  if (!temp.empty()) {
    tokens.push_back(temp);
  }
  return tokens;
}
