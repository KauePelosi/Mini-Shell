#include "history.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

History::History() {
  const char *home = getenv("HOME");
  if (!home) {
    historyFile = ".minishell_history";
  } else {
    historyFile = std::string(home) + "/.minishell_history";
  }
}

void History::load() {
  std::ifstream file(historyFile);
  if (!file.is_open()) {
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      history.push_back(line);
    }
  }
}

void History::add(const std::string &command) {
  if (command.empty()) {
    return;
  }
  history.push_back(command);
  appendToFile(command);
}

void History::appendToFile(const std::string &command) {
  std::ofstream file(historyFile, std::ios::app);
  if (!file.is_open()) {
    std::cerr << "MiniShell-> Failed to write history\n";
    return;
  }
  file << command << '\n';
}

const std::vector<std::string> &History::entries() const { return history; }
