# Data Compression and Decompression Tool

This project is a versatile file compression tool that implements multiple compression algorithms: Huffman, Asymmetric Numeral System (ANS), LZ77, and Run-Length Encoding (RLE). This tool is designed for efficient data compression and decompression, with flexibility to choose the best algorithm for different types of data.

## Table of Contents
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Compression Algorithms](#compression-algorithms)
  - [Huffman](#huffman)
  - [ANS (Asymmetric Numeral System)](#ans-asymmetric-numeral-system)
  - [LZ77](#lz77)
  - [RLE (Run-Length Encoding)](#rle-run-length-encoding)
- [File Handling](#file-handling)
- [Utils](#utils)
- [Submodules](#submodules)
- [Contributing](#contributing)
- [License](#license)


- **Multiple Compression Algorithms:** Supports Huffman, ANS, LZ77, and RLE compression techniques.
- **Custom File Handling:** Includes utilities for reading and writing files in a compression-friendly format.
- **Command-Line Interface (CLI):** Provides a simple CLI for compressing and decompressing files with a specified algorithm.
- **Flexible and Modular:** Each algorithm is implemented in a separate module for easy expansion and customization.

## Project Structure

```plaintext
tiny_file.exe/
├── include/                     # Header files
├── src/                         # Source files
│   ├── main.c                   # CLI entry point
│   ├── huffman/                 # Huffman compression and decompression
│   ├── ans/					 # Asymmetric Numeral System
│   ├── lz77/					 # Repetition and Pattern Matching
│   ├── rle/                     # RLE compression and decompression
│   ├── file_io/                 # File handling functions
│   └── utils/                   # Utility functions
├── libft/                       # Submodule for libft (with printf and get_next_line)
├── _obj/                        # Compiled object files (auto-generated)
├── Makefile                     # Makefile to compile and link the project
└── README.md                    # Project description and instructions
```
---

## Installation

### Prerequisites
- **Git**: To clone the repository and submodules.
- **C Compiler**: GCC or Clang to build the project.

1. **Clone the repository**:
   ```bash
   git clone https://github.com/EstivalSolstice/TinyFile.git
   cd tiny_file.exe

2. **Initialize Submodules**:
   ```bash
   make submodule_rebuild

3. **Compile the project**:
	```bash
	make

4. **Run the executable**:
	```markdown
	After building, you can run `tiny_file.exe` from the command line.
---

## Usage

### Basic Commands

- **Compress a file**:
	```bash
	./tiny_file.exe compress <algorithm> <input_file> <output_file>
- **Decompress a file**:
	```bash
	./tiny_file.exe decompress <algorithm> <input_file> <output_file>

### Parameters

- `<algorithm>`: Choose one of `huffman`, `ans`, `lz77`, or `rle`.
- `<input_file>`: The path to the file to compress or decompress.
- `<output_file>`: The path to save the compressed or decompressed output.
---

## Compression Algorithms

```markdown
Each algorithm has strengths suited for different types of data:

### Huffman

- **Directory**: src/huffman/
- **Description**: Huffman coding is a widely used method for entropy-based compression. It assigns shorter codes to more frequent symbols, achieving optimal compression for known, fixed-frequency data.
- **Best For**: Data with skewed symbol distributions.

### ANS (Asymmetric Numeral System)

- **Directory**: src/ans/
- **Description**: ANS is an efficient entropy coding algorithm that adapts well to skewed distributions and is often faster than traditional arithmetic coding.
- **Best For**: High-speed compression on data with variable frequencies.

### LZ77

- **Directory**: src/lz77/
- **Description**: LZ77 is a dictionary-based compression technique that replaces repeated sequences with references to earlier occurrences. It’s ideal for data with repeated phrases or patterns.
- **Best For**: Text files, logs, and structured data with redundancy.

### RLE (Run-Length Encoding)

- **Directory**: src/rle/
- **Description**: RLE is a simple compression technique that encodes consecutive identical symbols as a single symbol and count. It’s especially effective on data with long runs of repeated symbols.
- **Best For**: Images, raw data, or simple graphical data with repetitive symbols.
---

## This project is licensed under the MIT License.

---
## Acknowledgments

```markdown
This project was inspired by common data compression techniques and aims to provide a practical learning experience in implementing efficient compression algorithms.
