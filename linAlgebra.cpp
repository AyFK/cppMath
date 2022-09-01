#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <random>


#include <ttmath/ttmath.h>
typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(128)> massDouble;

typedef double defaultType;

struct linAlg {


    template<typename type>
    void delMatrix(type** matrix, int row) {
        for (int i = 0; i < row; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }



    template<typename type>
    type** copyMatrix(type** matrix, int row, int col) {
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
    type** randMatrix(int row, int col, double minVal=-1, double maxVal=1) {
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
    void scalarMult(type** matrix, int row, int col, double scalar) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (matrix[i][j] != 0) {
                    matrix[i][j] *= scalar;
                }
            }
        }
    }



    template<typename type>
    type** dotProduct(type** matrixA, int dimA, type** matrixB, int dimB) {
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
    void printMatrix(type** matrix, int row, int col) {
        for (int i = 0; i < row; i++) {
            std::cout << "\n";

            for (int j = 0; j < col; j++) {
                std::cout << matrix[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
};

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

    std::cin.get();

    return 0;
}
