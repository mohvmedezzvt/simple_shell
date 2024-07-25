# 0x16. C - Simple Shell

A simple UNIX command line interpreter that replicates the basic functionalities of a shell. This project is implemented in C and provides basic command execution along with some built-in commands.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Files](#files)
- [Authors](#authors)

## Features
- Executes commands from standard input.
- Supports built-in commands like `cd`, `exit`, `env`, `setenv`, and `unsetenv`.
- Handles command execution with arguments.
- Includes error handling.
- Supports both interactive and non-interactive modes.

## Requirements
- GCC compiler
- Unix-like operating system (Linux, macOS)

## Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/mohvmedezzvt/simple_shell.git
    ```

2. Navigate to the project directory:
    ```sh
    cd simple_shell
    ```

3. Compile the source code:
    ```sh
    gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
    ```

## Usage
1. Run the shell:
    ```sh
    ./hsh
    ```

2. Use the shell like a standard Unix shell. For example:
    ```sh
    #cisfun: ls -l
    #cisfun: pwd
    #cisfun: cd /path/to/directory
    #cisfun: echo "Hello, world!"
    ```

3. To exit the shell, use the `exit` command or press `Ctrl+D`.

## Built-in Commands
The Simple Shell includes the following built-in commands:

- `cd [directory]`: Change the current directory to `directory`.
- `exit [status]`: Exit the shell with an optional exit status.
- `env`: Print the current environment.
- `setenv VARIABLE VALUE`: Set a new environment variable or modify an existing one.
- `unsetenv VARIABLE`: Unset an environment variable.

## Files
- `hsh.c`: Entry point of the shell program and main loop.
- `hsh.h`: Header file with function prototypes and macro definitions.
- `builtins.c`: Implementation of built-in commands.
- `execution.c`: Functions related to command execution.
- `handlings.c`: Functions for reading and parsing input, and handling the PATH.
- `AUTHORS`: List of contributors to the project.

## Authors
See the [AUTHORS](./AUTHORS) file for a list of contributors to this project.

Feel free to contribute to this project by forking the repository and submitting pull requests. Your contributions are welcome!
