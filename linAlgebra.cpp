#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <random>

#include "exports.h"

//typedef double defaultType;


template<typename type>
void linAlg::delMatrix(type** matrix, int row) {
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
}



template<typename type>
type** linAlg::copyMatrix(type** matrix, int row, int col) {
    type** newMatrix;
    size_t rowSize = row * sizeof(type*);
    size_t colSize = col * sizeof(type);
    newMatrix = (type**) malloc(rowSize);

    for (int i = 0; i < row; i++) {
        newMatrix[i] = (type*) malloc(colSize);

        for (int j = 0; j < col; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    return newMatrix;
}




template<typename type>
type** linAlg::randMatrix(int row, int col, double minVal, double maxVal) {
    type** matrix;
    size_t rowSize = row * sizeof(type*);
    size_t colSize = col * sizeof(type);
    matrix = (type**) malloc(rowSize);

    int seed = rand();
    std::default_random_engine generator(seed);

    for (int i = 0; i < row; i++) {
        matrix[i] = (type*) malloc(colSize);

        for (int j = 0; j < col; j++) {
            std::uniform_real_distribution<double> dist(minVal, maxVal);
            type randVal = dist(generator);
            matrix[i][j] = randVal;
        }
    }
    return matrix;
}



template<typename type>
type** linAlg::identityMatrix(int row, int col) {
    type** matrix;
    size_t rowSize = row * sizeof(type*);
    size_t colSize = col * sizeof(type);
    matrix = (type**) malloc(rowSize);

    for (int i = 0; i < row; i++) {
        matrix[i] = (type*) malloc(colSize);

        for (int j = 0; j < col; j++) {

            if (i == j) {
                matrix[i][j] = 1;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}



template<typename type>
void linAlg::scalarMult(type** matrix, int row, int col, double scalar) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] != 0) {
                matrix[i][j] *= scalar;
            }
        }
    }
}



template<typename type>
type** linAlg::dotProduct(type** matrixA, int dimA, type** matrixB, int dimB) {
    // calculate product of two equal symmetric matrices
    // ASSUMPION : matrixA and matrixB are of equal 'type'
    type** product;
    size_t rowSize = dimA * sizeof(type*);
    size_t colSize = dimB * sizeof(type);

    product = (type**) malloc(rowSize);

    for (int i = 0; i < dimA; i++) {
        product[i] = (type*) malloc(colSize);


        for(int j = 0; j < dimB; j++) {
            product[i][j] = 0;

            for(int k = 0; k < dimB; k++) {
                product[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return product;
}



template<typename type>
type** linAlg::transposed(type** matrix, int row, int col) {
    type** newMatrix;
    size_t rowSize = col * sizeof(type*);
    size_t colSize = row * sizeof(type);

    newMatrix = (type**) malloc(rowSize);

    for (int j = 0; j < col; j++) {
        newMatrix[j] = (type*) malloc(colSize);

        for (int i = 0; i < row; i++) {
            newMatrix[j][i] = matrix[i][j];
        }
    }
    return newMatrix;
}



template<typename type>
double linAlg::determinant(type** matrix, int dim) {
    // credit: @lastchance (5801)
    // source: https://www.cplusplus.com/forum/beginner/267880/

    const double limit = 1.0e-30;
    double det = 1;
    type** matrixDecoy = copyMatrix<type>(matrix, dim, dim);

    for (int i = 0; i < (dim - 1); i++) {

        // partial pivot: find row r below with largest element in column i
        int r = i;
        type maxMatrix = std::abs(matrixDecoy[i][i]);

        for (int k = i + 1; k < dim; k++) {
            double val = std::abs(matrixDecoy[k][i]);

            if (val > maxMatrix) {
                r = k;
                maxMatrix = val;
            }
        }

        if (r != i) {
            for (int j = i; j < dim; j++ ) {
                std::swap(matrixDecoy[i][j], matrixDecoy[r][j]);
            }
            det = -det;
        }

        // row operations to make upper-triangular
        double pivot = matrixDecoy[i][i];

        if (std::abs(pivot) < limit) {
            std::cout << "\nDeterminant ∄ for singular matrices\n";
            return 0.0;
        }

        for (int r = i + 1; r < dim; r++) {
            double multiple = matrixDecoy[r][i] / pivot;

            for (int j = i; j < dim; j++) {
                matrixDecoy[r][j] -= multiple * matrixDecoy[i][j];
            }
        }
        det *= pivot; // det() = product of diagonal
    }
    det *= matrixDecoy[dim-1][dim-1];
    delMatrix<type>(matrixDecoy, dim); // remove decoy from heap

    return det;
}


template<typename type>
void linAlg::inverse(type** matrix, int dim) {
    // code inspired by source i accidentally lost...

    type** augmentedMatrix;
    size_t rowSize = dim * sizeof(type*);
    size_t colSize = 2 * dim * sizeof(type);

    augmentedMatrix = (type**) malloc(rowSize);

    for (int i = 0; i < dim; i++) {
        augmentedMatrix[i] = (type*) malloc(colSize);

        for (int j = 0; j < (2 * dim); j ++) {

            // fill w/ original matrix
            if (j < dim) {
                augmentedMatrix[i][j] = matrix[i][j];
            }

            // fill diagonal w/ 1
            else if (j == (i + dim)) {
                augmentedMatrix[i][j] = 1;
            }

            // fill rest w/ 0
            else {
                augmentedMatrix[i][j] = 0;
            }
        }
    }

    // gauss jordan elimination
    double temp;

    for (int i = 0; i < dim; i++) {
        temp = augmentedMatrix[i][i];

        for (int j = i; j < (2 * dim); j++) {
            augmentedMatrix[i][j] = augmentedMatrix[i][j] / temp;

            if (i == (dim - 1) and j >= dim) {
                // put solution into 'matrix'
                matrix[i][j-dim] = augmentedMatrix[i][j];
            }
        }

        for(int j = 0; j < dim; j++) {

            if(i != j) {
                temp = augmentedMatrix[j][i];

                for(int k = 0; k < (2 * dim); k++) {
                    augmentedMatrix[j][k] = augmentedMatrix[j][k] -
                                            (temp * augmentedMatrix[i][k]);

                    if (i == (dim - 1) and k >= dim) {
                        // put solution into 'matrix'
                        matrix[j][k-dim] = augmentedMatrix[j][k];
                    }
                }
            }
        }
    }

    delMatrix<type>(augmentedMatrix, dim);
}



template<typename type>
void linAlg::printMatrix(type** matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
        std::cout << "\n";

        for (int j = 0; j < col; j++) {
            std::cout << matrix[i][j] << " ";
        }
    }
    std::cout << "\n";
}



/*
int main() {
    srand(time(NULL));

    linAlg OBJ; int row = 3; int col = 3;

    defaultType** matrixA = OBJ.randMatrix<defaultType>(row, col);
    OBJ.printMatrix<defaultType>(matrixA, row, col);

    defaultType** matrixB = OBJ.randMatrix<defaultType>(row, col);
    OBJ.printMatrix<defaultType>(matrixB, row, col);


    defaultType** matrixC = OBJ.dotProduct<defaultType>(matrixA, row, matrixB,
                                                        row);
    OBJ.printMatrix<defaultType>(matrixC, row, col);

    OBJ.scalarMult<defaultType>(matrixC, row, col, -1);
    OBJ.printMatrix<defaultType>(matrixC, row, col);


    defaultType** identMatrix = OBJ.identityMatrix<defaultType>(row, col);
    OBJ.scalarMult<defaultType>(identMatrix, row, col, -1);
    OBJ.printMatrix<defaultType>(identMatrix, row, col);


    std::cout << "\ndeterminant and inverse of matrixA =";
    OBJ.printMatrix<defaultType>(matrixA, row, col);

    double det = OBJ.determinant<defaultType>(matrixA, row);
    std::cout << "\n" << det << "\n";

    OBJ.inverse<defaultType>(matrixA, row);
    OBJ.printMatrix<defaultType>(matrixA, row, col);

    std::cin.get();

    return 0;
}
*/
