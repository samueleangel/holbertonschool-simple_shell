# Simple Shell

A simple UNIX command interpreter written in C as part of the Holberton School curriculum.

## Description
This shell is a lightweight clone of the Bourne shell (sh) with basic functionality:
- Executes commands with their full path
- Handles command lines with arguments
- Implements built-ins like `exit` and `env`
- Manages the PATH environment variable
- Supports both interactive and non-interactive modes

## Installation
Clone the repository and compile:
```bash
git clone https://github.com/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
