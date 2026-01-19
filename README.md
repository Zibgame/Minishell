# 🐚 Minishell

Minishell is a minimal shell inspired by Bash.  
It executes commands, handles pipes, redirections and environment variables.  
It includes built-ins such as `cd`, `echo`, `pwd`, `export`, `unset`, `env` and `exit`.

## 🎯 Goals

- Interactive shell prompt
- Command history
- Redirections `<`, `>`, `<<`, `>>`
- Pipe support `|`
- Environment variables expansion (`$HOME`, `$?`)
- Signal handling (ctrl-C, ctrl-D, ctrl-\)
- Built-ins included

## ⚙️ Build & Run

```bash
make
./minishell
```

# ✨ Optional Bonus

Wildcards *

Logical operators && and ||
s