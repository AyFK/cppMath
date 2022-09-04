#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <random>


typedef double defaultType;

#include "exports.h"



// MINDstorming

/*
normal distribution to Z-distribution
----
Linear transformation X ~ N(E[x], V[x]) to Y := (X - E[x]) / D[x] ~ N(0, 1)

Z-distribution back to normal distribution
----
Redo linear transformation Y ~ N(0, 1) to X := D[x]*Y + E[x] ~ N(E[x], V[x])
*/



/*
V[X + Y] = V[X] + V[Y] + 2C[X, Y] (1)
V[X - Y] = V[X] + V[Y] - 2C[X, Y] (2)
- - - - - - - - - - - - - - - - - - -

if: A_1 = a_1 + a_2, yield:
V[A_1] = V[a_1 + a_2] according to (1)

and: A_2 = a_1 + a_2 + a_3 = A_1 + a_3, yield:
V[A_2] = V[A_1 + a_3] according to (1)

a recursive method to minimize variance could be applied, no?
*/



