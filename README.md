# Addition-Subtraction Compiler

This is my first brush with building a compiler in C.

![Compiler Logo](screenshots/screenshot1.png)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)


## Introduction

The **Addition-Subtraction Compiler** is a simple compiler written in C that translates a custom language supporting basic arithmetic operations—specifically addition and subtraction—into C code. This project serves as an educational tool to understand the fundamental concepts of compiler construction, including lexical analysis, parsing, abstract syntax tree (AST) generation, and code generation.

## Features

- **Print Statements:** Output the result of arithmetic expressions.
- **Arithmetic Operations:** Supports addition (`+`) and subtraction (`-`).
- **Error Handling:** Detects and reports syntax errors with line numbers.

## Installation

### Prerequisites

- **GCC Compiler:** Ensure you have GCC installed.
  
    gcc --version

    If not installed, install it using:

    - **Ubuntu/Debian:**

        sudo apt-get update
        sudo apt-get install build-essential

    - **macOS (using Homebrew):**

        brew install gcc

- **Make:** Make sure `make` is installed. It typically comes pre-installed on most Unix-like systems.

### Clone the Repository

    git clone https://github.com/ThadPinch/add-subtract-language.git
    cd add-subtract-language

### Build the Compiler

Navigate to the project directory and run:

    make

This command compiles the source code and generates the `simple_compiler` executable.

## Usage

To compile a source program written in the custom language (`.simple` files) into C code:

    ./simple_compiler <source_file.simple> <output_file.c>

**Example:**

    ./simple_compiler program.simple output.c

After generating the C code, compile it using `gcc`:

    gcc -o output output.c

Run the executable:

    ./output

## Examples

### Sample Source Program (`program.simple`)

    print 3 + 4 - 2;
    print 10 - 5 + 8;

### Generated C Code (`output.c`)

    #include <stdio.h>
    
    int main() {
        printf("%d\n", (3 + 4 - 2));
        printf("%d\n", (10 - 5 + 8));
        return 0;
    }

### Execution Output

    $ ./output
    5
    13

