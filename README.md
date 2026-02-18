# MiniShell

A **minimal Unix-like shell written in C++**, developed as a **personal portfolio project**. MiniShell focuses on demonstrating strong fundamentals in **operating systems**, **process management**, **command execution**, and **clean, extensible C++ design**.

This project is intentionally scoped: it is not meant to replace Bash or Zsh, but to show **how a shell works internally**, with emphasis on clarity and correctness.

---

## Features

### Implemented

*   Interactive prompt displaying the **current working directory (cwd)**
*   Command input via `std::getline`
*   Custom **tokenizer** with support for single and double quotes
*   Execution of external commands using:

    *   `fork()`
    *   `execvp()`
    *   `waitpid()`
*   Built-in command system with dynamic dispatch
*   Implemented built-ins:

    *   `cd` (defaults to `$HOME`)
    *   `exit [status]`
*   Clear separation between:

    *   internal commands (built-ins)
    *   external system commands
*   Modular project structure (`src/` / `include/`)
*   Fully functional compiled binary

---

## Architecture Overview

The project is designed to be **simple to follow**, while remaining **easy to extend**.

### Execution Flow

```
User Input
   ↓
Tokenization
   ↓
Dispatcher
   ├─ Built-in command
   └─ External command (fork + exec)
```

### Built-in Dispatching

Built-ins are registered in an `unordered_map`, allowing new commands to be added **without modifying the dispatcher logic**.

---

## Build System (CMake)

MiniShell utilizes **CMake** as its build system, adhering to modern, target-based practices.

CMake is primarily responsible for **generating build files** (such as `Makefiles` or `Ninja files`), rather than directly compiling the source code.

### Build Flow (Mental Model)

```
CMakeLists.txt
      ↓
cmake -B build
      ↓
Build System Files (Makefile / Ninja)
      ↓
cmake --build build
      ↓
MiniShell Executable
```

### Basic Concepts

#### Project

```cmake
project(MiniShell LANGUAGES CXX)
```

This command defines the project's name and specifies the programming languages it uses (e.g., CXX for C++). It's a foundational declaration and does not, by itself, initiate any compilation or linking.

#### Targets

In CMake, a 
target is any artifact that CMake is configured to build. This can include executables, libraries, or other custom outputs.

**Examples:**
*   **Executable Target:** `add_executable(MiniShell)`
*   **Library Target:** `add_library(minishell_lib)`

All build configurations, such as source files, compile options, and link libraries, are associated with specific targets.

#### Source Files

Source files are explicitly linked to a target, informing CMake which files are part of a particular build artifact:

```cmake
target_sources(MiniShell PRIVATE
  src/main.cpp
  src/core/shell.cpp
  src/core/tokenize.cpp
)
```

This declaration ensures that the specified source files are compiled and linked as part of the `MiniShell` executable target.

#### Include Directories

Include directories specify the locations where the compiler should search for header files (`.hpp`, `.h`).

```cmake
target_include_directories(MiniShell PRIVATE include)
```

By setting this, you can use clean, absolute includes relative to the specified directory, such as:

```cpp
#include "core/shell.hpp"
```

This approach is preferred over using relative paths (e.g., `../`) within source files, which can lead to brittle build configurations.

#### Compile Options

Compiler warnings and flags are applied to specific targets to enforce coding standards and enable diagnostic checks:

```cmake
target_compile_options(MiniShell PRIVATE
  -Wall
  -Wextra
  -pedantic
)
```

These options help maintain code quality and catch potential issues during compilation.

#### Build Types

CMake supports different build types, which control optimization levels and the inclusion of debugging symbols. The build type is selected during the configuration step, not within the `CMakeLists.txt` file itself.

**Common Build Types:**
*   `Debug`: Optimized for debugging, with minimal or no optimizations and full debug symbols.
*   `Release`: Optimized for performance, with maximum optimizations and no debug symbols.
*   `RelWithDebInfo`: Optimized for performance, but includes debug symbols for easier post-mortem debugging.
*   `MinSizeRel`: Optimized for the smallest possible binary size.

To specify a build type during configuration:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

### Common CMake Commands

#### 1. Configure the Project

This command should be executed when setting up the project for the first time or after any modifications to the `CMakeLists.txt` files.

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

This step performs the following actions:
*   Creates the `build/` directory if it doesn't already exist.
*   Generates the native build system files (e.g., `Makefile` for Make, or `build.ninja` for Ninja).
*   Generates the `compile_commands.json` file, which is crucial for various development tools.

#### 2. Build the Project

After configuring, this command compiles all defined targets within the project:

```sh
cmake --build build
```

#### 3. Clean Rebuild

If the build becomes corrupted or inconsistent, a clean rebuild can resolve issues by removing all generated build artifacts and reconfiguring from scratch:

```sh
rm -rf build
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### `clangd` Integration

Language Servers like `clangd` rely on the `compile_commands.json` file to accurately understand include paths, compiler flags, and other project-specific settings. This enables features like intelligent autocompletion, diagnostics, and refactoring.

After configuring your project with CMake, it's recommended to create a symbolic link to `compile_commands.json` in the project root:

```sh
ln -sf build/compile_commands.json .
```

# Generate the compile_commands.json:
```
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

This ensures that `clangd` (or any other tool looking for this file in the project root) can easily locate it, preventing false 
errors related to 
false include errors and improving the overall development experience.

### Output Binary

If the `RUNTIME_OUTPUT_DIRECTORY` property is set in CMake, the final executable will be placed in a specified directory. For example:

```cmake
set_target_properties(MiniShell PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
```

With this configuration, the compiled executable will be found at:

```
bin/MiniShell
```

### Design Philosophy

*   All configuration is **target-based**, ensuring modularity and clarity.
*   **No relative includes (`../`)** are used in source files; header paths reflect the `include/` directory structure for better maintainability.
*   The project structure is designed for **future expansion**, accommodating additional libraries, tests, and tools.

---

## Project Structure

```
MiniShell/
├── bin/            # Compiled executable output
├── build/          # CMake build artifacts
├── include/        # Public header files
│   ├── built-ins/  # Headers for built-in commands
│   │   ├── builtCd.hpp
│   │   ├── builtExit.hpp
│   │   └── builtHistory.hpp
│   ├── core/       # Core shell component headers
│   │   ├── dispatcher.hpp
│   │   ├── externalCommands.hpp
│   │   ├── shell.hpp
│   │   └── tokenize.hpp
│   ├── utils/      # Utility function headers
│   │   ├── getInternMap.hpp
│   │   ├── history.hpp
│   │   ├── historyGlobal.hpp
│   │   └── printCwd.hpp
│   └── config.hpp  # Global configuration header
├── src/            # Source code files
│   ├── built-ins/  # Source for built-in commands
│   │   ├── builtCd.cpp
│   │   ├── builtExit.cpp
│   │   └── builtHistory.cpp
│   ├── core/       # Core shell component sources
│   │   ├── dispatcher.cpp
│   │   ├── externalCommands.cpp
│   │   ├── shell.cpp
│   │   └── tokenize.cpp
│   ├── utils/      # Utility function sources
│   │   ├── getInternMap.cpp
│   │   ├── history.cpp
│   │   ├── historyGlobal.cpp
│   │   └── printCwd.cpp
│   └── main.cpp    # Main application entry point
├── CMakeLists.txt  # CMake build configuration
├── compile_commands.json -> build/compile_commands.json # Symlink for Language Servers
└── README.md       # Project README file
```

---

## Technologies and Concepts

*   Modern C++ (C++17 / C++20)
*   Unix/Linux system programming
*   Process creation and management
*   File system navigation
*   Low-level system calls
*   STL containers and algorithms
*   Modular and extensible design

---

## Roadmap

The following roadmap is organized by **impact and technical depth**, with portfolio value in mind.

### High Priority (Core Shell Features)

*   [ ] Pipe support (`|`)
*   [ ] Input/output redirection (`>`, `>>`, `<`)
*   [ ] Proper signal handling (`SIGINT`, Ctrl+C)
*   [ ] Return status of the last executed command (`$?`)
*   [x] Command history (in-memory)

### Medium Priority (Shell Behavior and Usability)

*   [ ] Environment variable expansion (`$VAR`)
*   [ ] Built-in `export` and `unset`
*   [ ] Tilde expansion (`~`)
*   [ ] Improved parser (state machine or simple AST)
*   [ ] Error messages closer to real shells

### Advanced / High-Value Enhancements

*   [ ] Pipeline execution with multiple processes
*   [ ] Job control basics (`fg`, `bg`, `jobs`)
*   [ ] Background execution (`&`)
*   [ ] Logical operators (`&&`, `||`)
*   [ ] Subshell execution (`(command)`)

### Low Priority (Polish and Portfolio Extras)

*   [ ] Config file support (`.minishellrc`)
*   [ ] Customizable prompt
*   [ ] Debug / verbose mode
*   [ ] Automated tests
*   [ ] Simple performance benchmarks

---

## Goals of the Project

MiniShell exists to:

*   Demonstrate solid understanding of **Unix internals**
*   Show clean, maintainable **C++ system-level code**
*   Highlight architectural thinking, not just features
*   Serve as a strong **portfolio project** for systems / backend roles

---

## How to Run

```bash
./bin/main.out
```

---

## Project Status

*   Stable core with clean architecture
*   Missing classic shell features by design (planned)
*   Strong foundation for incremental evolution

---

## License

Personal project developed for educational and portfolio purposes.
