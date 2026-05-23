<div align="center">

<h1>🔮 Curio</h1>
<h3>A Statically Typed Interpreted Programming Language, Built From Scratch in C</h3>

<p>
  <img src="https://img.shields.io/badge/C-GCC%208+-00599C?style=flat-square&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/License-MIT-22c55e?style=flat-square" alt="MIT License" />
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-64748b?style=flat-square" alt="Platform" />
  <img src="https://img.shields.io/badge/Status-Active-22c55e?style=flat-square" alt="Active" />
  <img src="https://img.shields.io/badge/Dependencies-Zero-f97316?style=flat-square" alt="Zero Dependencies" />
</p>

<p>
  <strong>Curio</strong> is a fully self-contained statically typed interpreted programming language written entirely in C.<br/>
  It features an English-like syntax with explicit block terminations, a direct-dispatch execution model,<br/>
  and a custom symbol table — with no external libraries, parser generators, or runtime dependencies.
</p>

</div>

---

## Table of Contents

- [Overview](#overview)
- [Architecture](#architecture)
- [Features](#features)
- [Type System](#type-system)
- [Syntax Reference](#syntax-reference)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Design Decisions](#design-decisions)
- [Current Limitations](#current-limitations)
- [Roadmap](#roadmap)
- [License](#license)

---

## Overview

Curio is built **100% from scratch in C** — no LLVM, no Flex, no Bison. Every layer of the language is a custom, hand-written implementation:

- **Hand-rolled Tokenizer** — A finite-state machine lexer processes source code line-by-line, emitting a structured stream of typed `Token` structs with no regular expression engine involved.
- **Direct-Dispatch Execution Model** — Curio deliberately avoids building an Abstract Syntax Tree. A central dispatcher matches the leading token of each statement to its handler and executes immediately — a lean, transparent model ideal for studying bare-metal text-to-action translation.
- **Custom Symbol Table & Memory Model** — Variables are managed via linearly allocated arrays simulating a bounded frame environment, with no heap allocator or garbage collector involved.
- **Block Resolution via Forward Scanning** — Control flow blocks (`if`, `while`, `repeat`) are resolved at runtime using forward-scanning algorithms that locate their matching terminators (`endif`, `endwhile`, `endrepeat`) procedurally — no pre-compilation step required.
- **Strict Static Typing** — All types are resolved at declaration time, eliminating dynamic coercion bugs and preserving runtime safety throughout execution.
- **Zero External Dependencies** — Not a single third-party parsing or runtime library.

---

## Architecture

A raw `.cuo` script is transformed into executed operations through a clean, linear pipeline:

```
  .cuo Source File
        │
        ▼
  ┌─────────────┐
  │   main.c    │  Opens the script file, drives line-by-line execution
  └──────┬──────┘
         │
         ▼
  ┌──────────────────┐
  │   Tokenizer      │  Lexes each line → typed Token array
  │   tokenizer.c    │  (keywords, identifiers, literals, operators, block markers)
  └──────┬───────────┘
         │
         ▼
  ┌──────────────────┐
  │   Interpreter    │  Direct-dispatch execution — no AST; central dispatcher
  │   interpreter.c  │  matches the leading token of each statement to its handler
  └──────┬───────────┘
         │
         ├──────────────────────────┬──────────────────────────┐
         ▼                          ▼                          ▼
  ┌─────────────────┐   ┌──────────────────────┐   ┌──────────────────┐
  │  Assignment     │   │  Control Flow        │   │  Symbol Table    │
  │  assignment.c   │   │  control_flow.c      │   │  symbol_table.c  │
  │                 │   │                      │   │                  │
  │  Variable state │   │  if/else, while,     │   │  Linearly        │
  │  mutation and   │   │  repeat; forward-    │   │  allocated       │
  │  type checking  │   │  scan block resolver │   │  variable frame  │
  └─────────────────┘   └──────────────────────┘   └──────────────────┘
         │
         ▼
  ┌──────────────────┐
  │  Error System    │  Line-level diagnostic reporting with descriptive messages
  │  error.c         │
  └──────────────────┘
```

---

## Features

### Static Type System
All variables are explicitly declared with `make` and assigned with `set`. Type mismatches are caught and reported immediately — no implicit coercion.

### Control Flow
Full conditional branching and bounded / conditional iteration, all with explicit unambiguous terminators:

- `if / else / endif`
- `while ... do / endwhile`
- `repeat <n> times / endrepeat`
- `break` and `continue` inside any loop body

### Input & Output
- `print` — writes to stdout; supports inline variable interpolation via `{varname}` syntax and `<nl>` as a newline escape
- `take` — reads typed input from stdin directly into a declared variable

### Comments
Single-line comments are supported using the `#` prefix. Everything after `#` on a line is ignored by the tokenizer.

```
# This is a comment
make whole age     # inline comment
set age = 25
```

### String Interpolation
Variables are embedded directly in string literals using `{curly brace}` syntax — no format specifiers or concatenation operators needed.

### Arithmetic
Linear token-based arithmetic evaluation across `whole`, `real`, and `symbol` types using standard operators `+`, `-`, `*`, `/`.

---

## Type System

| Curio Type | Declaration | Assignment | C Storage |
|------------|-------------|------------|-----------|
| Integer | `make whole age` | `set age = 25` | `int` |
| Floating Point | `make real pi` | `set pi = 3.14` | `double` |
| Character | `make symbol grade` | `set grade = 'A'` | `char` |
| String | `make string name` | `set name = "Alice"` | `char[]` |
| Boolean | `make bool active` | `set active = true` | `int` (mapped) |

---

## Syntax Reference

All logic blocks require explicit termination markers. Comments use the `#` prefix.

```
# ════════ VARIABLES ════════════════
make whole age
set age = 25

make real score
set score = 91.5

make string name
set name = "Alice"

make bool active
set active = true

# ════════ OUTPUT & INPUT ════════════
print "Hello, {name}!<nl>"

make string input
take string input
print "You entered: {input}<nl>"

# ════════ CONDITIONALS ══════════════
if age > 18 then
    print "Access granted.<nl>"
else
    print "Access denied.<nl>"
endif

# ════════ WHILE LOOP ════════════════
make whole i
set i = 3

while i > 0 do
    print "Countdown: {i}<nl>"
    set i = i - 1
endwhile

# ════════ REPEAT LOOP ═══════════════
repeat 5 times
    print "Polling...<nl>"
endrepeat

# ════════ LOOP CONTROL ══════════════
while active == true do
    print "Running...<nl>"
    break
endwhile
```

---

## Project Structure

```
curio/
├── examples/
│   ├── demo.cuo              # Full syntax demonstration script
│   └── hello.cuo             # Looping and standard I/O example
│
├── include/
│   ├── assignment.h          # State mutation declarations
│   ├── control_flow.h        # Branching and looping logic declarations
│   ├── error.h               # Error handling definitions
│   ├── interpreter.h         # Dispatcher declarations
│   ├── symbol_table.h        # Variable environment tracking
│   └── tokenizer.h           # Lexical analysis rules and Token definitions
│
├── src/
│   ├── assignment.c          # Variable assignment and type validation
│   ├── control_flow.c        # if/else, while, repeat — forward-scan resolvers
│   ├── error.c               # Error formatting and diagnostic output
│   ├── interpreter.c         # Primary direct-dispatch execution loop
│   ├── main.c                # Entry point and file I/O
│   ├── symbol_table.c        # Linear frame allocation and variable lookup
│   └── tokenizer.c           # Finite-state machine string tokenization engine
│
├── LICENSE
└── README.md
```

---

## Getting Started

### Prerequisites

A standard C compiler: `gcc` (GCC 8+), `clang`, or MSVC. No libraries or package managers required.

### Clone

```bash
git clone https://github.com/kashyap-devansh/curio.git
cd curio
```

### Compile

```bash
gcc src/*.c -I include -o curio -O3 -Wall
```

### Run a Script

```bash
# Unix / macOS / Linux
./curio examples/demo.cuo

# Windows
.\curio examples/demo.cuo
```

### Example

```
make string name
make whole score

set name = "Alice"
set score = 87

print "Student: {name}<nl>"
print "Score:   {score}<nl>"

if score >= 90 then
    print "Grade: A<nl>"
else
    if score >= 75 then
        print "Grade: B<nl>"
    else
        print "Grade: C<nl>"
    endif
endif

make whole countdown
set countdown = 3

while countdown > 0 do
    print "Countdown: {countdown}<nl>"
    set countdown = countdown - 1
endwhile

print "Done.<nl>"
```

**Output:**

```
Student: Alice
Score:   87
Grade: B
Countdown: 3
Countdown: 2
Countdown: 1
Done.
```

---

## Design Decisions

**Why direct-dispatch instead of an AST?**
Direct-dispatch enabled rapid, focused development of a fully functional linear execution pipeline. AST generation introduces non-trivial memory allocations and complex tree-node management — deliberately deferred to keep the initial architecture lean and debuggable.

**Why explicit block terminators?**
C-style braces complicate the lexical grammar. Explicit tokens like `endif` and `endwhile` simplify the forward-scanning block resolver and eliminate all ambiguity in nested control structures.

**Why static typing?**
Statically resolving types at declaration time eliminates dynamic coercion bugs and preserves runtime safety — a deliberate contrast to the permissive typing found in languages like PHP or JavaScript.

**Why C as the host language?**
Implementing in C forces direct engagement with memory layout, string handling, and pointer arithmetic. Every design decision becomes visible and intentional — there is no managed runtime to hide behind.

---

## Current Limitations

Curio is intentionally scoped at this stage:

- No user-defined functions or call stacks
- No expression precedence parser — arithmetic is resolved linearly, left-to-right
- No Abstract Syntax Tree (AST)
- No bytecode compiler or virtual machine
- Variables are statically scoped without runtime reallocation
- Limited standard library
- Line-level error diagnostics only — no column precision yet

---

## Roadmap

Upcoming development will focus on deeper architectural rigor:

- **Pratt / Recursive Descent Parser** — correct operator precedence and complex expression support
- **Abstract Syntax Tree (AST)** — transition from linear dispatch to formal tree-based evaluation for nested and compound expressions
- **User-defined Functions** — frame allocation, parameter passing, and properly scoped variable environments
- **Bytecode Compiler & VM Stack** — intermediate representation for improved performance and cross-platform portability
- **Enhanced Diagnostics** — column-level precision, stack traces, and richer error context messages

---

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

<div align="center">
  <sub>Developed to practically explore language design and interpreter architecture in C.</sub>
</div>