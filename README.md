# 🐚 minishell

A **tcsh-like Unix shell** written in C, built as part of the EPITECH curriculum.

---

## 📖 Overview

`minishell` (`mysh`) is a lightweight Unix shell that replicates core behaviors of the tcsh shell. It supports command execution, piping, I/O redirections, environment management, and a set of built-in commands — all implemented from scratch in C.

---

## 🗂️ Project Structure

```
minishell/
├── main.c
├── Makefile
├── include/
├── lib/my/
├── src/
│   ├── base_shell/
│   ├── builtins/
│   │   ├── base/
│   │   └── bonus/
│   ├── pipes/
│   └── redirections/
└── assets/
```

---

## ✨ Features

- **Interactive prompt** (`> `) with SIGINT handling (Ctrl+C)
- **Command execution** — runs binaries found in `PATH`
- **Pipes** — chain commands with `|`
- **I/O Redirections** — `>`, `<`, `>>`
- **Environment management** — inherits and manages `env` variables
- **Built-in commands** (see below)
- **Custom `libmy`** — a hand-rolled utility library (string ops, printf, etc.)

---

## 🔧 Built-in Commands

| Command | Description |
|---------|-------------|
| `env` | Display all environment variables |
| `cd [dir]` | Change the current directory |
| `exit [status]` | Exit the shell with an optional status code |
| `help` | Display help information about the different custom buitins |
| `rick` | Bonus surprise |
| `boubou` | Another bonus surprise |

---

## 🚀 Getting Started

### Prerequisites
- `make`
- Linux

### Build

```bash
make
```

This compiles the custom `libmy.a` library and links the final `mysh` executable.

### Run

```bash
./mysh
```

You'll be greeted with the `> ` prompt.

### Clean

```bash
make clean
make fclean
make re
make debug
```

---

## 💡 Usage Examples

```sh
> ls -la
> echo hello | cat -e
> cat file.txt > output.txt
> cd /tmp && pwd
> env
> exit 0
```

---

## 🧩 Architecture

The shell follows a classic **read → parse → execute** loop:

1. **`main_loop`** — reads user input and drives the REPL
2. **`parse_command`** — tokenizes and structures the input
3. **`find_cmd`** — resolves the command path via `PATH`
4. **`exec_command`** — forks and executes the command, or dispatches to a built-in
5. **Pipes & Redirections** — handled as preprocessing steps before execution

---

## 📄 License

This project was made for the **EPITECH** curriculum (2026). It is intended for educational purposes.
