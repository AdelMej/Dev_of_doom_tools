## Dev_of_doom_tools ⚒️👾

A template project for building and testing C programs following Holberton-style rules.

---

## 🚀 Features

- 🧩 Compile Holberton main files located in the `holberton/` directory (e.g., `0-main.c`, `1-main.c`).
- 🧪 Compile and run unit tests located in the `tests/` directory, supporting any `test_*.c` files.
- 🎯 Capture stdout and stderr output during tests for precise verification.
- 🔧 Flexible Makefile to build binaries and run tests with ease.
- 📁 Automatic creation of build (`build/`) and object (`obj/`) directories.

---

## 🗂️ Project Structure
```yaml
Dev_of_doom_tools/
├── holberton/
│   └── 999-main.c        # Holberton main source files
├── tests/
│   ├── test_*.c          # Unit test source files
│   ├── template.c        # Basic empty test template
│   ├── capture.c         # Capture helper implementations
│   └── capture.h         # Capture helper declarations
├── obj/                  # Object files (generated)
├── build/                # Binaries (generated)
├── main.c                # Simple hello world main
├── Makefile
└── .gitignore

```


---

## ⚙️ How to Use

### Build all 🔨

```bash
make
Compiles all Holberton mains and tests, producing executables in the build/ folder.

Run tests ✅❌
```bash
make test
```

Runs all unit tests, showing pass/fail status.

Run a specific test 🎯
```bash
make run-test_testname
```

Example:

```bash
make run-test_test_capture
```

Clean build files 🧹
```bash
make clean
```
Removes all generated object files and binaries.

---

## 📦 Template Files Included

- `tests/template.c` — A basic empty test file to help you get started quickly 🧪✨  
- `holberton/999-main.c` — A placeholder main file for Holberton-style compilation practice 🕹️  
- `main.c` — A simple program that prints "Hello, World" for sanity checking your build setup 👋🌍  

These templates make it easy to test your setup and add new features or tests without starting from scratch.

📝 Notes
🔍 The Makefile auto-detects Holberton main files in holberton/ and test files in tests/.

📂 Object files go to obj/, and executables go to build/.

🛡️ Uses gcc with strict flags (-Wall -Wextra -Werror -pedantic -std=gnu89) for clean, portable C code.

🧪 Uses Unity testing framework with helpers to capture output.

✨ Feel free to customize the Makefile to fit your project’s needs!

Happy coding! 💻🔥 Tools for the fallen you'll find all you need to fight against c shenanigans
