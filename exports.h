


struct linAlg {

    template<typename type>
    void delMatrix(type** matrix, int row);

    template<typename type>
    type** copyMatrix(type** matrix, int row, int col);

    template<typename type>
    type** randMatrix(int row, int col, double minVal=-1, double maxVal=1);

    template<typename type>
    type** identityMatrix(int row, int col);

    template<typename type>
    void scalarMult(type** matrix, int row, int col, double scalar);

    template<typename type>
    type** dotProduct(type** matrixA, int dimA, type** matrixB, int dimB);

    template<typename type>
    type** transposed(type** matrix, int row, int col);

    template<typename type>
    double determinant(type** matrix, int dim);

    template<typename type>
    void inverse(type** matrix, int dim);

    template<typename type>
    void printMatrix(type** matrix, int row, int col);

};


struct stats : public linAlg {

    void TEST();

};
