#pragma once
#include "core/shellContext.hpp"
#include <string>
#include <vector>

int pipelineCommands(const std::vector<std::vector<std::string>> &pipeCommands,
                     ShellContext &ctx);
