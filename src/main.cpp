
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "json.hpp"

#include "sci_constants.h"

/**
 * @brief Calculate the length of wire in a solenoid
 *
 * Uses numerical integration to calculate the length of wire.
 * 
 * @param coilLength The length of the solenoid in meters(m)
 * @param radius The radius of the solenoid in meters(m)
 * @param numTurns How many turns of wire are in the solenoid
 * @param numIntervals How many integration intervals to divide the coil into
 * @return The length of wire in the solenoid in meters(m)
 */
double calculateWireLength(double coilLength, double radius, double numTurns, long numIntervals) {
    double length = 0;
    double intervalLength = coilLength / numIntervals;
    double omega = 2 * PI * numTurns / coilLength;

    for (long i=0; i<numIntervals; i++) {
        double x = i * intervalLength;

        double dx = intervalLength;
        double dy = radius * omega * -sin(omega * x) * intervalLength;
        double dz = radius * omega * cos(omega * x) * intervalLength;

        length += sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
    }

    return 2 * length;
}

/**
 * @brief Calculate the length of wire in a solenoid
 *
 * Uses numerical integration to calculate the length of wire.
 * Overloads @see double calculateWireLength(double coilLength, double radius, double numTurns, int numIntervals)
 * to use a default value of 100 intervals per turn of wire. 
 * 
 * 
 * @param coilLength The length of the solenoid in meters(m)
 * @param radius The radius of the solenoid in meters(m)
 * @param numTurns How many turns of wire are in the solenoid
 * @return The length of wire in the solenoid in meters(m)
 */
double calculateWireLength(double coilLength, double radius, long numTurns) {
    long numIntervals = numTurns * 100;

    return calculateWireLength(coilLength, radius, numTurns, numIntervals);
}

/**
 * @brief Calulate the resistance of a cylindrical solenoid
 * 
 * @param wireLength The length of the wire wrapped aroudn the solenoid in meters(m)
 * @param wireResistivity The resistivity of the wire in ohm-meters(Ω * m)
 * @param wireDiameter The diameter of the wire in meters(m)
 * @return The resistance of the wire in ohms(Ω) 
 */
double calculateSolenoidResistance(double wireLength, double wireResistivity, double wireDiameter) {
    // The cross-sectional area of the wire
    double radius = wireDiameter / 2;
    double area = PI * pow(radius, 2);

    // The resistance of the wire
    return wireLength * wireResistivity / area;
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
 * @param numTurns How many turns of wire are in the solenoid
 * @param length The length of the solenoid in meters(m)
 * @param current The current flowing through the solenoid in Amperes(A)
 * @return The magnitude of the magnetic field produced by the solenoid in Teslas(T)
 */
double calculateSolenoidMagneticField(double effectivePermeability, double numTurns, double length, double current)
{
    return MU_0 * effectivePermeability * numTurns / length * current;
}

int main()
{
    // std::cout << "Wire diameter:";
    // std::cin >> wireDiameter;
    
    

    return EXIT_SUCCESS;
}