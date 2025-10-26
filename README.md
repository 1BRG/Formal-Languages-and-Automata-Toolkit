# Formal Languages and Automata Toolkit

[![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Build System](https://img.shields.io/badge/build-CMake-green.svg)](https://cmake.org/)

A comprehensive C++ toolkit for modeling, executing, and analyzing algorithms from the theory of formal languages and automata. This project, built from first principles, provides high-performance implementations of Finite Automata (NFAs, DFAs), regular expression engines, and Context-Free Grammar (CFG) parsers.

## Features

-   **Finite Automata Engine (NFA/DFA)**
    -   Parse NFA/DFA configurations from custom input files.
    -   Full **Regex -> NFA -> DFA** conversion pipeline.
    -   **Regular Expression Parsing** using Shunting-Yard and Thompson's Construction to build an NFA.
    -   **NFA to DFA conversion** via Subset Construction algorithm.
    -   High-throughput string validation for any defined automaton.
-   **Context-Free Grammar (CFG) Module**
    -   Load and process **any valid CFG** from a standardized input format.
    -   Generate valid strings from the grammar using a manual **backtracking** algorithm.
    -   Produce the **leftmost derivation** path for a given target string.
    -   Efficiently validate string membership using **prefix pruning** to optimize recognition.
-   **Bonus: Context-Sensitive Language Analysis**
    -   Includes a "simulated" recognizer for the context-sensitive language `a^n b^n c^n`.
    -   Procedural verification and in-code comments explain why this language **cannot be parsed by a CFG** (i.e., requires more than one stack).

## Project Structure

The project is organized into a modular structure with separate directories for headers and source files.

```
LFA/                             # Project Root
├── cmake-build-debug/           # CLion build directory
├── include/                     # Header files (.h/.hpp)
│   ├── Automat.h                # Part of Automata module
│   ├── Input.h                  # Part of Automata module
│   ├── Sigma.h                  # Part of Automata module
│   ├── States.h                 # Part of Automata module
│   ├── Transitions.h            # Part of Automata module
│   ├── json.hpp                 # nlohmann::json for parsing tests
│   └── CFG.h                    # Context-Free Grammar module
├── src/                         # Source files and resources
│   ├── main.cpp                 # Entry point (Task 1, 2, 3, Bonus)
│   ├── Automat.cpp              # Part of Automata module
│   ├── Transitions.cpp          # Part of Automata module
│   ├── States.cpp               # Part of Automata module
│   ├── Sigma.cpp                # Part of Automata module
│   ├── Input.cpp                # Part of Automata module
│   ├── CFG.cpp                  # Context-Free Grammar module
│   ├── LFA-Assignment2_Regex_DFA.json  # JSON tests for Regex->DFA
│   ├── aSb.in                   # Example CFG: S → aSb | ε
│   └── aNbNcN.in                # Bonus CFG for a^n b^n c^n
├── input.txt                    # NFA/DFA configuration for Task 1
├── CMakeLists.txt               # CMake configuration for all tasks
└── README.md                    # Project documentation
```
## Getting Started

### Prerequisites

-   A C++ compiler (g++, Clang, etc.)
-   CMake (version 3.10 or higher)

### Building and Running

#### Using CLion (Recommended)

1.  Go to `File > Open` and select the root directory `LFA/`.
2.  CLion will automatically configure the CMake project.
3.  `Build > Build Project` (or `Ctrl+F10`).
4.  `Run > Edit Configurations...` and create run configurations for `tema1`, `tema2`, `tema3`, and `bonusTema3`.

#### Using the Command Line (Linux)

```bash
# Create a build directory
mkdir -p build && cd build

# Configure the project with CMake
cmake ..

# Compile the project
cmake --build .

# To run the executables:
./run_automat tema1        # Task 1: NFA/DFA from input.txt
./run_automat tema2        # Task 2: Regex → DFA (JSON tests)
./run_automat tema3        # Task 3: CFG S→aSb|ε (generate, derive, recognize)
./run_automat bonusTema3   # Bonus: a^n b^n c^n (CFG + procedural verify)
```


## Core Components & Implementation

### Finite Automata Module (Tasks 1 & 2)

-   **`Automat`**: The central class that parses NFAs/regex, builds the automaton, and handles the conversion to a DFA.
-   **`States`, `Sigma`, `Transitions`, `Input`**: Support classes for reading configurations and managing the components of an automaton.
-   **Key Algorithms Implemented**:
    -   **Shunting-Yard & Thompson's Construction**: To parse a regular expression and build an equivalent NFA.
    -   **Subset Construction**: To convert an NFA into a DFA, eliminating non-determinism.

### Context-Free Grammar Module (Task 3)

-   **`CFG.h / CFG.cpp`**: The `CFG` class provides the core functionality:
    -   The constructor can parse **any valid context-free grammar** from a file, not just the example `aSb.in`.
    -   `generate(maxLen, maxCount)`: Generates valid strings using a manual backtracking implementation.
    -   `derivation(target)`: Returns the steps of the leftmost derivation for a target string.
    -   `recognize(target)`: Validates string membership using prefix pruning for enhanced efficiency.
-   **`main.cpp`**: The `tema3()` function calls these methods to demonstrate the functionality.

### Architectural Decisions

1.  **Manual Backtracking**: The CFG generator was implemented without external libraries to demonstrate a deep understanding of the algorithm.
2.  **Prefix Pruning**: The CFG recognizer uses prefix checking to efficiently discard invalid derivation paths early, significantly improving performance.
3.  **Modular Design**: Each major component (Automata, CFG) is encapsulated in its own set of classes and files for clarity and maintainability.
4.  **CMake Build System**: The project is configured with CMake to handle all build tasks and dependencies cleanly across different environments.

## Usage Example (CFG Module)

Running the executable for Task 3 demonstrates the CFG capabilities.

```bash
./run_automat tema3
```

**Example Output:**

```
Words generated by the grammar S→aSb|ε (max 10 words, each max 10 characters):
ε
ab
aabb
aba…

Derivation of the word "aaabbb":
S -> aSb -> aaSbb -> aaaSbbb -> aaabbb

Recognition for "aaaabbb": Fals
```

---

*Project for the Formal Languages and Automata course - University of Bucharest*
