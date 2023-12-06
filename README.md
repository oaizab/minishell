# Minishell

Minishell is a simple Unix shell written in C, designed to provide a basic command-line interface with features inspired by the Bash shell. It is a part of the 42 School curriculum and aims to implement various functionalities commonly found in popular shells.

## Features

- **Prompt Display:** Minishell displays a user-friendly prompt when waiting for a new command.

- **Command History:** The shell maintains a working history of commands for easy navigation.

- **Command Execution:** Minishell searches for and launches the right executable based on the PATH variable or using a relative or absolute path.

- **Quoting Handling:**
  - Does not interpret unclosed quotes or special characters unnecessary for the subject (e.g., `\` or `;`).
  - Handles single quotes (`'`) to prevent the shell from interpreting meta-characters in the quoted sequence.
  - Handles double quotes (`"`) to prevent the shell from interpreting meta-characters in the quoted sequence except for `$` (dollar sign).

- **Redirections:**
  - `<` redirects input.
  - `>` redirects output.
  - `<<` with a delimiter reads input until a line containing the delimiter is seen (without updating history).
  - `>>` redirects output in append mode.

- **Pipes:** Implements pipes (`|`) where the output of each command in the pipeline is connected to the input of the next command via a pipe.

- **Environment Variables:** Handles `$` followed by a sequence of characters, expanding to their values.

- **Special Variables:**
  - Handles `$?`, which expands to the exit status of the most recently executed foreground pipeline.

- **Signal Handling:**
  - Handles `ctrl-C`, `ctrl-D`, and `ctrl-\` similar to their behavior in Bash.
    - `ctrl-C`: Displays a new prompt on a new line.
    - `ctrl-D`: Exits the shell.
    - `ctrl-\`: Does nothing.

- **Built-in Commands:**
  - `echo` with the option `-n`.
  - `cd` with only a relative or absolute path.
  - `pwd` with no options.
  - `export` with no options.
  - `unset` with no options.
  - `env` with no options or arguments.
  - `exit` with no options.

- **Logical Operators:**
  - `&&` and `||` with parentheses for priorities.

- **Wildcard Support:**
  - Wildcards (`*`) work for the current working directory.

## Getting Started

To compile Minishell, use the provided Makefile:

```bash
make
```

Run the shell:

```bash
./minishell
```

## Usage

Minishell provides a command-line interface where you can enter commands and explore various shell functionalities. Use **ctrl-D** to exit the shell.
