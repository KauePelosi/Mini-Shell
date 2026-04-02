# Pipeline Execution (Pipes)

## Overview

This update introduces initial support for **command pipelines** using the pipe operator (`|`).

A pipeline allows multiple commands to be connected so that the output of one becomes the input of the next.

Example:

```bash
ls -l | grep cpp | wc -l
```

---

## Motivation

Previously, the shell only supported executing a **single command at a time**.

However, real shells support chaining commands through pipes, which requires:

* Multiple processes
* Inter-process communication (IPC)
* Coordinated execution

This change introduces the foundation for that behavior.

---

## Design Decision

Instead of modifying the existing execution logic, a new layer was introduced:

```text
tokens → pipeline parsing → execution
```

This keeps the architecture clean and avoids breaking existing functionality.

---

## Parsing Strategy

The tokenizer remains mostly unchanged.

Input like:

```bash
ls -l | grep cpp | wc -l
```

Is tokenized as:

```cpp
["ls", "-l", "|", "grep", "cpp", "|", "wc", "-l"]
```

A new step splits tokens into commands:

```cpp
[
  ["ls", "-l"],
  ["grep", "cpp"],
  ["wc", "-l"]
]
```

---

## Execution Strategy

For a pipeline with N commands:

* N processes are created (`fork`)
* N-1 pipes are created (`pipe`)
* File descriptors are redirected using `dup2`

Each process:

* Reads from the previous command (if not first)
* Writes to the next command (if not last)

---

## Key Concepts

### Pipe (`pipe()`)

Creates a unidirectional communication channel:

* `fd[0]` → read end
* `fd[1]` → write end

---

### Fork (`fork()`)

Creates a child process:

* Returns `0` in the child
* Returns child PID in the parent

---

### Duplication (`dup2()`)

Redirects standard streams:

* `STDIN_FILENO` (0)
* `STDOUT_FILENO` (1)

---

### Exec (`exec*`)

Replaces the current process with a new program.

---

## Integration

Execution flow:

```cpp
auto pipeline = splitPipeline(tokens);

if (pipeline.size() == 1) {
    dispatcher(pipeline[0], ctx);
} else {
    executePipeline(pipeline, ctx);
}
```

---

## Current Status

* Basic pipeline parsing implemented
* Initial execution logic under development
* Edge cases not yet handled (e.g., invalid syntax)

---

## Future Improvements

* Error handling for invalid pipelines
* Integration with redirections (`>`, `<`)
* Built-in command compatibility
* Refactor execution logic to reduce duplication

---

## Notes

This implementation is intentionally incremental.

Focus was placed on:

* Understanding process communication
* Building a correct mental model
* Keeping the architecture extensible

Further refinements will follow.
