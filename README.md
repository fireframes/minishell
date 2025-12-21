# Minishell

A minimal shell implementation based on Bash, developed as part of the 42 Core curriculum.

## Description

This project implements a command-line interpreter that manages process lifecycles, file descriptors, and system signals. It utilizes a custom lexer and parser to transform user input into an executable command tree.

## Features

* **Command Execution**: Supports absolute/relative paths and binary lookup via the `PATH` environment variable.
* **Built-in Commands**:
   * `echo` (with `-n` option)
   * `cd`
   * `pwd`
   * `export`
   * `unset`
   * `env`
   * `exit`
* **Redirections**:
   * `<`: Input redirection
   * `>`: Output redirection (truncate)
   * `>>`: Output redirection (append)
   * `<<`: Heredoc
* **Pipelines**: Supports `|` for inter-process communication via pipes.
* **Environment Variables**: Expansion of `$VAR` and `$?` (exit status).
* **Signal Handling**:
   * In interactive mode:
      * `Ctrl-C`: Displays a new prompt on a new line.
      * `Ctrl-D`: Exits the shell.
      * `Ctrl-\`: Does nothing.
   * During command execution, signals behave like in Bash.

## Compilation and Usage

The project uses `make` for compilation.

```bash
# Compile the executable
make

# Run the shell
./minishell
```
