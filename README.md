<div align="center">
  <h1>Curio</h1>
  <p><b>A statically typed interpreted programming language exploring direct-dispatch execution.</b></p>
  
  [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
  [![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
  [![Platform](https://img.shields.io/badge/platform-win%20%7C%20mac%20%7C%20linux-lightgrey.svg)]()
</div>

<br />

Curio is a lightweight, statically typed interpreted programming language written entirely in C. It was designed to practically explore language theory, lexer implementation, and interpreter architecture, providing an English-like syntax structure that prioritizes explicit block terminations over traditional C-style delimiters (like semicolons and braces).

Unlike typical toy languages implementing dynamically typed interpreters atop high-level host languages, Curio implements a custom memory-efficient tokenization engine and a linear direct-dispatch execution model natively in C. It serves as an exploration of procedural execution, bounded state management, and parsing strategies without the overhead of heavy parser generators.

---

## Quick Example

Curio enforces an explicit, readable syntax flow using the `.cuo` extension.

```text
make string system_name
set system_name = "Curio Engine"

make whole cursor
set cursor = 5

print "Initializing {system_name}...<nl>"

while cursor > 0 do
    print "Reversing index: {cursor}<nl>"
    set cursor = cursor - 1
endwhile

print "Sequence complete.<nl>"
```

---

## Architecture & Execution Pipeline

Curio utilizes a two-phase pipeline emphasizing predictable memory usage and execution safety over complex tree building.

### 1. Tokenization (Lexical Analysis)
The source code is processed line-by-line by a highly optimized tokenization engine. Leveraging finite-state machine principles, it categorizes raw text into an array of strictly defined `Token` structs, identifying keywords, identifiers, literals, operators, and block markers.

### 2. Direct Interpretation (Execution Phase)
The execution engine avoids building an Abstract Syntax Tree (AST), instead employing a **direct-dispatch execution model**. A central dispatcher matches the primary token of a statement to its corresponding operational handler (e.g., assignment, I/O, looping), sequentially processing the tokenized logic.

### Memory & Block Management
Variables are managed via custom, linearly allocated arrays simulating a bounded frame environment. Curio enforces strict static typing at runtime.

Blocks for `if/else`, `while`, and `repeat` are handled procedurally during execution. Instead of pre-compiling block structures, the interpreter utilizes forward-scanning algorithms to match `do` or `then` blocks to their corresponding `endif`, `endwhile`, or `endrepeat` terminators.

---

## Project Structure

```text
curio/
├── examples/
│   ├── demo.cuo         # Syntax demonstration script
│   └── hello.cuo        # Looping and standard I/O example
├── include/
│   ├── assignment.h     # State mutation declarations
│   ├── control_flow.h   # Branching & looping logic
│   ├── error.h          # Error handling definitions
│   ├── interpreter.h    # Dispatcher declarations
│   ├── symbol_table.h   # Variable environment tracking
│   └── tokenizer.h      # Lexical analysis rules
├── src/
│   ├── assignment.c     # Variable assignment implementation
│   ├── control_flow.c   # Branching and loop parsers
│   ├── error.c          # Error formatting implementation
│   ├── interpreter.c    # Primary execution loop
│   ├── main.c           # Entry point and file IO
│   ├── symbol_table.c   # Memory allocation implementation
│   └── tokenizer.c      # String tokenization engine
├── LICENSE              # MIT License
└── README.md            # Project documentation
```

---

## Build & Run Instructions

Curio has minimal dependencies, compiling across major platforms with GCC, Clang, or MSVC.

```markdown
### Clone the Repository
```bash
git clone https://github.com/kashyap-devansh/curio.git
cd curio
```

### GCC Compilation
Compile the project utilizing standard optimization flags:

```bash
gcc src/*.c -I include -o curio -O3 -Wall
```

### Execution
Provide the `.cuo` source file as the first argument to the interpreter executable.

```bash
# Unix / macOS / Linux
./curio examples/demo.cuo

# Windows
.\curio examples/demo.cuo
```

---

## Language Reference

Curio enforces static typing and explicit terminators to ensure highly predictable execution paths.

### Variable Types
Initializations require the `make` keyword; derivations utilize the `set` keyword.

| Type | Syntax Example | Assignment Example | Underlying C Type |
| :--- | :--- | :--- | :--- |
| Integer | `make whole age` | `set age = 25` | `int` |
| Floating Point | `make real pi` | `set pi = 3.14` | `double` |
| Character | `make symbol grade` | `set grade = 'A'` | `char` |
| Text String | `make string name` | `set name = "Devansh"` | `char[]` |
| Boolean | `make bool active` | `set active = true` | `int` (mapped) |

### Control Flow
Logic blocks strictly mandate explicit termination markers.

```text
if cursor > 5 then
    print "Threshold exceeded.<nl>"
else
    print "Within safe parameters.<nl>"
endif
```

### Iteration
Curio implements conditional iteration (`while`) and bounded iteration (`repeat`), fully supporting `break` and `continue` semantics.

```text
repeat 3 times
    print "Polling endpoint...<nl>"
endrepeat
```

---

## Design Decisions

- **Why direct-dispatch execution?** It enables rapid feature development while preserving a lean, easily debuggable code base, offering clear insights into bare-metal text-to-action translation.
- **Why explicit block terminators?** C-style braces `{}` complicate parsing lexicons. Explicit tokens like `endif` simplify the forward-scanning parser and eliminate ambiguity within nested control structures.
- **Why was AST deferred?** Direct-dispatch allowed focusing heavily on a functional, linear execution pipeline. AST generation introduces non-trivial memory allocations and complex tree-node management which, initially, was deliberately avoided.
- **Why static typing?** Statically resolving types mitigates dynamic type-coercion bugs natively seen in PHP or JavaScript interfaces, preserving runtime safety.

---

## Current Limitations

Curio currently functions accurately within known constraints:
- Variables are statically scoped initially without deep runtime reallocation.
- No user-defined functions or call stacks.
- No expression precedence parser (strictly linear token resolution).
- No Abstract Syntax Tree (AST) implementation.
- No Bytecode/VM (Intermediate Representation).
- Limited Standard Library modules.
- Basic procedural, line-oriented error diagnostics.

---

## Roadmap

As a continuous compiler engineering exploration, upcoming implementations will emphasize architectural rigor:
- **Pratt or Recursive Descent Parser:** To correctly resolve true arithmetic operator precedence.
- **Abstract Syntax Tree (AST):** Transitioning from linear direct-dispatch to formal tree data modeling for complex nested expressions.
- **Function Definitions:** Implementing structural frame allocations to support parameter passing and scoping mechanisms within user-defined routines.
- **Bytecode & VM Stack:** Generating Intermediate Representation (IR) for significantly improved pre-runtime execution performance and code portability.
- **Enhanced Diagnostics:** Introducing precise column/line metrics alongside stack tracing.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

<div align="center">
  <i>Developed to practically explore language design and interpreter architecture in C.</i>
</div>
