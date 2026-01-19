#include "builtCd.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

bool builtCd(const std::vector<std::string> &tokens) {
  const char *path = nullptr;
  if (tokens.size() < 2) {
    path = getenv("HOME");
    if (!path) {
      std::cerr << "HOME is not defined\n";
      return false;
    }
  } else {
    path = tokens[1].c_str();
  }
  if (chdir(path) != 0) {
    perror("cd");
    return false;
  }
  return true;
}
