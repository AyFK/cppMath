#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <random>


typedef double defaultType;
const double tau = 6.28319;
const double e = 2.71828;

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


/*
void stats::TEST() {

    std::cout << tau << "\n" << e << "\n";

    //defaultType** matrixA = OBJ.randMatrix<defaultType>(row, col);

    //defaultType** M = randMatrix<defaultType>(3, 3);
    //printMatrix<defaultType>(matrixA, row, col);

}
*/



int main() {
    srand(time(NULL));




    linAlg OBJ_2;

    std::cout << OBJ_2.test; // works

    defaultType** M = OBJ_2.randMatrix<defaultType>(3, 3); // does not work


    return 0;
}

