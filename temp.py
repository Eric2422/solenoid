import math

import scipy
import scipy.constants
import scipy.integrate

coilLength = 7.62e-2
coilRadius = 0.15875e-2
numTurns = 56

def f(x):
    omega = 2 * scipy.constants.pi * numTurns / coilLength;

    dx = 1
    dy = coilRadius * omega * -math.sin(omega * x)
    dz = coilRadius * omega * math.cos(omega * x)
    return math.sqrt(dx**2 + dy**2 + dz**2)

print(scipy.integrate.quad_vec(f, 0, coilLength))