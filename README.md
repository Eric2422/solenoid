# Solenoid

A short C++ program to calculate the magnetic field produced by a solenoid.
All numbers are in SI units.

> [!NOTE]
> The accuracy of this program seems rather questionable.

## Table of Contents

- [Usage](#usage)
- [Acknowledgements](#acknowledgements)
  - [Demagnetizing Factors](#demagnetizing-factors)
  - [Screw Sizes](#screw-sizes)

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

## Acknowledgements

### Demagnetizing Factors

The estimations for demagnetizing factors is based on
"Simple and approximate expressions of demagnetizing factors of uniformly magnetized rectangular rod and cylinder", by M. Sato and Y. Ishii,
published in "Journal of Applied Physics, Volume 66, Issue 2, July 15, 1989, pp.983-985".
DOI: [10.1063/1.343481](https://doi.org/10.1063/1.343481)
A copy of the paper is available at [./ref/sato_demagnetizing_factors.pdf](./ref/sato_demagnetizing_factors.pdf).

### Screw Sizes

Additionally, [a chart of US screw sizes](./ref/screw_sizes.jpg) from [WOOD Magazine](https://files.woodmagazine.com/wp-content/uploads/pdfs/sites/49/2021/10/26/screwchart.pdf) is included.
