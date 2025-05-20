#include <cstdlib>
#include <iostream>
#include <cmath>

#include "sci_constants.h"

double calculateWireLength(double length, double radius, double turns) {
    double length = 0;

    
}

/**
 * @brief Calculate the approximate effective permeability of a cylinder.
 * 
 * Calculates the demagnetizing factor of a cylinder using a formula from:
 * Journal of Applied Physics 66, 983 (1989); https://doi.org/10.1063/1.343481
 * A copy is included [here](ref/sato_demagnetizing_factors.pdf)
 * 
 * @param radius The radius of the cylinder in meters(m)
 * @param length The length of the cylinder in meters(m)
 * @param relativePermeability The relative permeability of the cylinder's material in N * A^-2
 * @return The effective permeability of the cylinder in N * A^-2
 */
double calculateCylinderEffectivePermeability(double radius, double length, double relativePermeability)
{
    // The ratio of the cylinder's length to its diameter
    double n = length / (2 * radius);
    double demagnetizingFactor = 1.0 / (2 * (2 * n / sqrt(PI)) + 1.0);
    double effectivePermeability = relativePermeability / (1.0 + demagnetizingFactor * (relativePermeability - 1.0));

    return effectivePermeability;
}

/**
 * @brief Calculate the magnetic field produced by a solenoid
 * 
 * @param effectivePermeability The effective permeability of the solenoid core in N * A^-2
 * @param turns How many turns of wire are in the solenoid
 * @param length The length of the solenoid in meters(m)
 * @param current The current flowing through the solenoid in Amperes(A)
 * @return The magnitude of the magnetic field produced by the solenoid in Teslas(T)
 */
double calculateSolenoidMagneticField(double effectivePermeability, double turns, double length, double current) {
    return MU_0 * effectivePermeability * turns / length * current;
}

int main()
{
    double length;
    std::cout << "Length of solenoid(m):";
    std::cin >> length;

    double radius;
    std::cout << "Radius of solenoid(m):";
    std::cin >> radius;

    double turns;
    std::cout << "Number of turns:";
    std::cin >> turns;
    
    double wireResisitivity;
    std::cout << "Wire resistivity (ohms / m):";
    std::cin >> turns;
    
    double wireDiameter;
    std::cout << ":";
    std::cin >> turns;
    
    std::cout << MU_0;
    return EXIT_SUCCESS;
}