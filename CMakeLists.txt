cmake_minimum_required(VERSION 3.20)
project(MiniShell LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(MiniShell)

target_sources(MiniShell PRIVATE
  src/main.cpp
  src/core/shell.cpp
  src/core/tokenize.cpp
  src/core/dispatcher.cpp
  src/core/externalCommands.cpp
  src/built-ins/builtCd.cpp
  src/built-ins/builtExit.cpp
  src/built-ins/builtHistory.cpp
  src/utils/getInternMap.cpp
  src/utils/history.cpp
  src/utils/historyGlobal.cpp
  src/utils/printCwd.cpp
)

target_include_directories(MiniShell PRIVATE include)
target_compile_options(MiniShell PRIVATE -Wall -Wextra -pedantic -g)

set_target_properties(minishell PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
