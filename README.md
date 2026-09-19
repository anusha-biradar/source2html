# Source2HTML

A C-based project that reads a C source file and converts it into an HTML file.

## What this project does

The program takes a C source file as input, processes its contents and generates an HTML file that displays the source code in a readable format.

It also identifies comments and processes different parts of the source code while generating the HTML output.

## Features

* Reads C source code from a file
* Identifies comments in the source code
* Processes the source code using a parser
* Generates an HTML output file
* Uses CSS to format the generated HTML
* Separates parsing and HTML generation into different modules

## Concepts Used

* C programming
* File handling
* Strings
* Parsing
* Functions
* Pointers
* Modular programming
* HTML
* CSS

## Project Structure

```text id="6a0w2r"
source2html/
│
├── main.c
├── parser.c
├── parser.h
├── html.c
├── html.h
├── sample.c
├── style.css
└── README.md
```

### File Description

| File        | Purpose                                                  |
| ----------- | -------------------------------------------------------- |
| `main.c`    | Handles the main program flow and command-line arguments |
| `parser.c`  | Contains the source-code parsing logic                   |
| `parser.h`  | Contains parser declarations                             |
| `html.c`    | Handles HTML file generation                             |
| `html.h`    | Contains HTML-related declarations                       |
| `sample.c`  | Sample C source file used as input                       |
| `style.css` | CSS used to format the generated HTML                    |

## How it works

The program takes a C source file and processes it using the parser module.

The parser identifies the required parts of the source code, and the HTML module uses the processed information to generate the final HTML file.

The generated HTML file can then be opened in a web browser.

## How to Compile

Compile the project using:

```bash id="qj1v9v"
gcc main.c parser.c html.c -o s2html
```

Then run:

```bash id="9wqg7v"
./s2html sample.c
```

The program generates an HTML file that can be opened in a browser.

## What I Learned

This project helped me understand how a C program can process source-code files and generate output in another format.

It also gave me practical experience with parsing, file handling, modular programming and working with HTML and CSS from a C program.
