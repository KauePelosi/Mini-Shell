# MiniShell

A **minimal Unix-like shell written in C++**, developed as a **personal portfolio project**. MiniShell focuses on demonstrating strong fundamentals in **operating systems**, **process management**, **command execution**, and **clean, extensible C++ design**.

This project is intentionally scoped: it is not meant to replace Bash or Zsh, but to show **how a shell works internally**, with emphasis on clarity and correctness.

---

## Features

### Implemented

* Interactive prompt displaying the **current working directory (cwd)**
* Command input via `std::getline`
* Custom **tokenizer** with support for single and double quotes
* Execution of external commands using:

  * `fork()`
  * `execvp()`
  * `waitpid()`
* Built-in command system with dynamic dispatch
* Implemented built-ins:

  * `cd` (defaults to `$HOME`)
  * `exit [status]`
* Clear separation between:

  * internal commands (built-ins)
  * external system commands
* Modular project structure (`src/` / `include/`)
* Fully functional compiled binary

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

## Project Structure

```
MiniShell/
├── bin/            # Final executable
├── build/          # Compiled object files (.o)
├── include/        # Header files
│   ├── builtCd.hpp
│   ├── builtExit.hpp
│   ├── dispatcher.hpp
│   ├── externalCommands.hpp
│   ├── getInternMap.hpp
│   ├── shell.hpp
│   └── tokenize.hpp
├── src/            # Source files
│   ├── builtCd.cpp
│   ├── builtExit.cpp
│   ├── dispatcher.cpp
│   ├── externalCommands.cpp
│   ├── getInternMap.cpp
│   ├── shell.cpp
│   └── tokenize.cpp
├── compile_flags.txt
└── README.md
```

---

## Technologies and Concepts

* Modern C++ (C++17 / C++20)
* Unix/Linux system programming
* Process creation and management
* File system navigation
* Low-level system calls
* STL containers and algorithms
* Modular and extensible design

---

## Roadmap

The following roadmap is organized by **impact and technical depth**, with portfolio value in mind.

### High Priority (Core Shell Features)

* [ ] Pipe support (`|`)
* [ ] Input/output redirection (`>`, `>>`, `<`)
* [ ] Proper signal handling (`SIGINT`, Ctrl+C)
* [ ] Return status of the last executed command (`$?`)
* [x] Command history (in-memory)

### Medium Priority (Shell Behavior and Usability)

* [ ] Environment variable expansion (`$VAR`)
* [ ] Built-in `export` and `unset`
* [ ] Tilde expansion (`~`)
* [ ] Improved parser (state machine or simple AST)
* [ ] Error messages closer to real shells

### Advanced / High-Value Enhancements

* [ ] Pipeline execution with multiple processes
* [ ] Job control basics (`fg`, `bg`, `jobs`)
* [ ] Background execution (`&`)
* [ ] Logical operators (`&&`, `||`)
* [ ] Subshell execution (`(command)`)

### Low Priority (Polish and Portfolio Extras)

* [ ] Config file support (`.minishellrc`)
* [ ] Customizable prompt
* [ ] Debug / verbose mode
* [ ] Automated tests
* [ ] Simple performance benchmarks

---

## Goals of the Project

MiniShell exists to:

* Demonstrate solid understanding of **Unix internals**
* Show clean, maintainable **C++ system-level code**
* Highlight architectural thinking, not just features
* Serve as a strong **portfolio project** for systems / backend roles

---

## How to Run

```bash
./bin/main.out
```

---

## Project Status

* Stable core with clean architecture
* Missing classic shell features by design (planned)
* Strong foundation for incremental evolution

---

## License

Personal project developed for educational and portfolio purposes.
