# Procedural Maze Generator <img src="Images/Logo.png" alt="Logo" width="256" height="256" align="right"/>

## Overview

A project for procedurally generating and solving two-dimensional mazes using various algorithms.

The current available maze generation algorithms are:

- Binary Tree
- Sidewinder

## Dependencies

- C++ 23 (Tested with MSVC Version 19.37.32824)
- CMake (Minimum Version Required: 3.26)
- vcpkg
    - Google Test / Google Mock
    - OpenCV

## Building

1. Clone the repository and extract it to a directory.
2. Opena terminal and navigate to the directory.
3. First, run the following
   command: `cmake -B Build/ -S . -DCMAKE_TOOLCHAIN_FILE="path to vcpkg/scripts/buildsystems/vcpkg.cmake"`
4. Then, run the following command: `cmake --build Build/ --config Config`, where Config is either Debug or Release.
5. The executable will be located within the Build/Console/Config/ directory, where Config is either Debug or Release.
6. Copy the files in the Console/Resources/ directory to the directory where the executable is located.
7. Run the executable.

## Running Tests

1. Clone the repository and extract it to a directory.
2. Open a terminal and navigate to the directory.
3. First, run the following
   command: `cmake -B Build/ -S . -DCMAKE_TOOLCHAIN_FILE="path to vcpkg/scripts/buildsystems/vcpkg.cmake"`
4. Then, run the following command: `cmake --build Build/ --config Config`, where Config is either Debug or Release.
5. The executable will be located within the Build/Test/Config/ directory, where Config is either Debug or Release.
6. Run the executable using the terminal.

## Usage

### Commands

- `export` - Exports a grid, modified or unmodified, to a PNG image.
- `grid` - Generates a grid.
- `help` - Displays the name and description of all commands.
- `maze` - Modifies a grid by applying a maze generation algorithm.
- `quit` Quits the application.

To get more information about the available commands, please refer to the `help` command.

### Examples

#### Exporting a Grid to a PNG Image

  ```
  > export -f Output.png -bs 5 -cs 20
  ```

#### Generating a Grid of Size 20x20

  ```
  > grid -s 20
  ```

#### Getting Help for the 'grid' Command

  ```
  > help -c grid
  ```

#### Modifying a Grid Using the Binary Tree Algorithm with Randomized Seed

  ```
  > maze -a BinaryTree
  ```

#### Modifying a Grid Using the Sidewinder Algorithm with Seed 12345

  ```
  > maze -a Sidewinder -s 12345
  ```

## Sample Outputs

### Grid

<img src="Images/Grid.png" alt="Grid" width="410" height="410"/>

### Binary Tree Algorithm

<img src="Images/BinaryTree.png" alt="Binary Tree Maze" width="410" height="410"/>

### Sidewinder Algorithm

<img src="Images/Sidewinder.png" alt="Sidewinder Maze" width="410" height="410"/>