# Data Compression and Decompression Tool

This project is a command-line tool for compressing and decompressing text files using two algorithms: Huffman Coding and Run-Length Encoding (RLE). The tool is designed to reduce file sizes by encoding data efficiently and then restoring it to its original form.

## Features

- **Huffman Compression**: A binary-tree-based algorithm that compresses data based on character frequencies.
- **Run-Length Encoding (RLE)**: A simpler method for compressing sequences of repeated characters.
- **File Handling**: Reads input files and writes compressed data to custom-formatted files.

## Project Structure

tiny_file.exe/
├── include/                     # Header files
├── src/                         # Source files
│   ├── main.c                   # CLI entry point
│   ├── huffman/                 # Huffman compression and decompression
│   ├── rle/                     # RLE compression and decompression
│   ├── file_io/                 # File handling functions
│   └── utils/                   # Utility functions
├── libft/                       # Submodule for libft (with printf and get_next_line)
├── _obj/                        # Compiled object files (auto-generated)
├── Makefile                     # Makefile to compile and link the project
└── README.md                    # Project description and instructions
---

## Getting Started

### Prerequisites
- **Git**: To clone the repository and submodules.
- **C Compiler**: GCC or Clang to build the project.



### Setup Instructions

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/EstivalSolstice/TinyFile.git
   cd tiny_file.exe

2. **Initialize Submodules**:
   ```bash
   make submodule_rebuild

3. **Compile the project**
	```bash
	make

4. **Cleaning up**
	```bash
	make fclean

---

```markdown
## This project is licensed under the MIT License.