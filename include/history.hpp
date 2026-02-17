#pragma once
#include <string>
#include <vector>

class History {
public:
  History();

  void load();
  void add(const std::string &command);
  const std::vector<std::string> &entries() const;

private:
  std::vector<std::string> history;
  std::string historyFile;

  void appendToFile(const std::string &command);
};
