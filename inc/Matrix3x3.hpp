#ifndef __MATRIX3X3_H__
#define __MATRIX3X3_H__
#include "Vector3.hpp"
#include "Matrix.hpp"

/**
 * @file Instantiation of template class Matrix like Matrix3x3, Matrix2x2 and MatrixRot
 */

/**
 * @brief three dimentional double Vector
 */
typedef Matrix<double, 3, 3> Matrix3x3;

/**
 * @brief two dimentional double Vector
 */
typedef Matrix<double, 2, 2> Matrix2x2;

class MatrixRot: public Matrix3x3{
    public:
        /**
         * @brief Construct a new Matrix Rot object and fill like unit Matrix
         */
        MatrixRot();

        /**
         * @brief Construct a new Matrix Rot object and copy 
         * @param M Copieied Matrix
         */
        MatrixRot(const Matrix3x3 &M): Matrix3x3(M){}

        /**
         * @brief Construct a new Matrix Rot object and fill with rotating values
         * @param angle angle of rotation
         * @param axis of rotation ex. \p VectorZ , \p VectorX , \p VectorY
         */
        MatrixRot(double angle, const Vector3 &axis);
};

#endif // __MATRIX3X3_H__