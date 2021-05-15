#ifndef __MATRIX3X3_H__
#define __MATRIX3X3_H__
#include "Vector3.hpp"
#include "Matrix.hpp"

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
        MatrixRot():Matrix3x3(){}           
        MatrixRot(double angle, const Vector3 &axis);
};

#endif // __MATRIX3X3_H__