#include "externalCommands.hpp"
#include <cstdlib>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

int externalCommands(const std::vector<std::string> &tokens) {
  std::vector<char *> c_args;
  for (const auto &arg : tokens) {
    c_args.push_back(const_cast<char *>(arg.c_str()));
  }
  c_args.push_back(nullptr);
  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    return 1;
  } else if (pid == 0) {
    if (execvp(c_args[0], c_args.data()) == -1) {
      perror("MiniShell");
    }
    exit(EXIT_FAILURE);
  } else {
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      return WEXITSTATUS(status);
    }
  }

  return 0;
}
