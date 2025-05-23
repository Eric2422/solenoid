import math

import scipy
import scipy.constants
import scipy.integrate

coilLength = 0.0762
coilRadius = 0.1
numTurns = 30

def f(x):
    omega = 2 * scipy.constants.pi * numTurns / coilLength;

    dx = 1
    dy = coilRadius * omega * -math.sin(omega * x)
    dz = coilRadius * omega * math.cos(omega * x)
    return math.sqrt(dx**2 + dy**2 + dz**2)

print(scipy.integrate.quad_vec(f, 0, coilLength))