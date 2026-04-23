# Redirection

## What Is

Redirection is a shell operator which allow output commands
to be directed to specific files instead of the terminal.

Represented by these two symbols:
- `>`: Redirects output (overwrites the file).
- `>>`: Appends output (adds to end of the file).

### Example

`cat README.md > file.txt`

## How it works

In the example above, the command cat which reads the file README.md and would normally print it to the terminal.
However, by using the operator `>` **(Redirection Output)**, 
the output is sent directly to file.txt.

## In Memory

In memory, redirection uses the same principle as the pipe,
leveraging file descriptors and system calls like fork().

### Flow Example

`user input -> parser -> fork() -> open(file) -> 
dup2(file_fd, STDOUT) -> close(file_fd) -> execvp(command)`

### Step By Step

1. User Input

The Shell receives a user input by a string, such as `cat README.md > file.txt`.

2. Parser

The shell parses the string to identify the redirection operator (`>`). It separates the command
(`cat README.md`) from the target file (`file.txt`).

3. Fork()

The Shell creates a child process using fork(). This is crucial so the
redirection **only affects the command being executed**, without breaking the
main shell's connection to the terminal.

4. Open(file)

Inside the child process, the Shell calls `open()` (a system call) on the target file.
This returns a new **file descriptor (FD)** representing that file.

5. Dup2(file_fd, STDOUT)

The Shell uses dup2 to clone the file's FD into the **standard output (STDOUT)** slot.
From this point on, anything the process prints will go to the file.

6. Close(file_fd)

The original file descriptor is no longer needed since STDOUT now points to the same file,
the Shell closes it to keep the FD table clean.

7. Execvp(command)

Finally, the Shell calls execvp(). The command (e.g., `cat`) replaces the child process.
Since it inherits the modified FD table, it writes to the file "thinking" it is
still writing to the terminal.

8. Parent Wait

While the child executes the command, the parent shell uses wait() to stay idle.
Once the child process finishes, the shell returns to the prompt, ready for the next user input,
with its own terminal connection (FD 0, 1, 2) completely untouched.
