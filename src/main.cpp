
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "json.hpp"
using json = nlohmann::json;

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
double calculateWireLength(double coilLength, double coilRadius, double numTurns, long numIntervals)
{
    double length = 0;
    double intervalLength = coilLength / numIntervals;
    double omega = 2 * PI * numTurns / coilLength;

    for (long i = 0; i < numIntervals; i++)
    {
        double x = i * intervalLength;

        double dx = intervalLength;
        double dy = coilRadius * omega * -sin(omega * x) * intervalLength;
        double dz = coilRadius * omega * cos(omega * x) * intervalLength;

        length += sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
    }

    return length;
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
double calculateWireLength(double coilLength, double coilRadius, long numTurns)
{
    long numIntervals = numTurns * 100;

    return calculateWireLength(coilLength, coilRadius, numTurns, numIntervals);
}

/**
 * @brief Calulate the resistance of a cylindrical solenoid
 *
 * @param wireLength The length of the wire wrapped aroudn the solenoid in meters(m)
 * @param wireDiameter The diameter of the wire in meters(m)
 * @param wireResistivity The resistivity of the wire in ohm-meters(Ω * m)
 * @return The resistance of the wire in ohms(Ω)
 */
double calculateWireResistance(double wireLength, double wireDiameter, double wireResistivity)
{
    // The cross-sectional area of the wire
    double coilRadius = wireDiameter / 2;
    double area = PI * pow(coilRadius, 2);

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
double calculateCylinderEffectivePermeability(double coilRadius, double coilLength, double relativePermeability)
{
    // The ratio of the cylinder's length to its diameter
    double n = coilLength / (2 * coilRadius);
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

int main(int argc, char *argv[])
{
    std::ifstream file = std::ifstream(argv[1]);
    json data = json::parse(file);
    file.close();

    std::string fields[] = {"coilLength", "coilRadius", "numTurns", "relativePermeability", "wireDiameter", "wireResistivity", "voltage"};
    for (const auto &field : fields)
    {
        if (!data.contains(field))
        {
            std::cerr << "The JSON is missing the \"" << field << "\" field." << std::endl;

            return EXIT_FAILURE;
        }
    }

    double effectivePermeability = calculateCylinderEffectivePermeability(data["coilRadius"], data["coilLength"], data["relativePermeability"]);

    std::cout << "Effective permeability = " << effectivePermeability << " N * A^-2" << std::endl;

    double wireLength = calculateWireLength(data["coilLength"], data["coilRadius"], data["numTurns"]);
    double wireResistance = calculateWireResistance(wireLength, data["wireDiameter"], data["wireResistivity"]);
    double current = data["voltage"].get<double>() / wireResistance;

    std::cout << "Wire length = " << wireLength << " m" << std::endl;
    std::cout << "Wire resistance = " << wireResistance << " Ω" << std::endl;
    std::cout << "Current = " << current << " A" << std::endl;

    double magneticField = calculateSolenoidMagneticField(effectivePermeability, data["numTurns"], data["coilLength"], current);

    std::cout << "B = " << magneticField << " T" << std::endl;

    return EXIT_SUCCESS;
}