# Solenoid

A short C++ program to calculate the magnetic field produced by a solenoid.
All numbers are in SI units.

> [!NOTE]
> The accuracy of this program seems rather questionable.

## Table of Contents

- [Usage](#usage)
- [References](#references)

## Usage

The program reads from JSON files in [`input/`](./input/).
The JSON should contain the following properties, each with a numeric value:

- `coilLength`
- `coilRadius`
- `numTurns`
- `relativePermeability`
- `wireDiameter`
- `wireResistivity`
- `voltage`

To run the calculations, first compile [`main.cpp`](./src/main.cpp) using your preferred compiler,
e.g., [G++](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/), etc.

Then run the binary file, passing in the path of the desired JSON as a command-line argument.
Assuming that the binary file is in `bin/`, run `bin/<name of binary file> <path to JSON file>`.

## References

M. Sato, Y. Ishii. (1989). Simple and approximate expressions of demagnetizing factors of uniformly magnetized rectangular rod and cylinder.
*Journal of Applied Physics* 66, 983 (1989); <https://doi.org/10.1063/1.343481>.
A copy of the paper is available at [./ref/sato_demagnetizing_factors.pdf](./ref/sato_demagnetizing_factors.pdf).

Screwchart. (2021). *WOOD Magazine*. <https://files.w2oodmagazine.com/wp-content/uploads/pdfs/sites/49/2021/10/26/screwchart.pdf>.
A copy is available at [./ref/screw_sizes.jpg](./ref/screw_sizes.jpg).
