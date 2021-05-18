#ifndef __MATRIXROT_H__
#define __MATRIXROT_H__
#include "Vectors.hpp"
#include "Matrix.hpp"

/**
 * @file Instantiation of template class Matrix like Matrix4x4, Matrix3x3, Matrix2x2 and MatrixRot
 */

#ifndef MIN_DIFF
    /**
     * @brief Minimal difference between two double numbers. It might be included from config.hpp
     */
    #define MIN_DIFF 0.000000001 
#endif // !MIN_DIFF

/**
 * @brief Square Matrix with double values and comare with MIN_DIFF
 * @tparam dim 
 */
template<std::size_t dim>
class dMatrixSqr: public Matrix<double, dim, dim>{
    public:
        /**
         * @brief Construct a new d Matrix Sqr object
         */
        dMatrixSqr(): Matrix<double, dim, dim>() {}

        /**
         * @brief Construct a new d Matrix Sqr object
         * @param list of inserted values
         */
        dMatrixSqr(const std::initializer_list<Vector<double, dim>> &list): Matrix<double, dim, dim>(list) {}

        /**
         * @brief Construct a new d Matrix Sqr object
         * @param M copied Matrix
         */
        dMatrixSqr(const Matrix<double, dim, dim> &M): Matrix<double, dim, dim>(M){}

        /**
         * @brief Checks if every diffrence is bigger  than MIN_DIFF
         * @param v compared dMatrixSqe
         * @return true if is lower
         * @return false if is bigger 
         */
        bool operator==(const dMatrixSqr &v) const{
            for (std::size_t i = 0; i < dim; ++i)
                for (std::size_t j = 0; j < dim; ++j)
                    if (abs(this->vector[i][j] - v[i][j]) > MIN_DIFF)
                        return false;
            return true;
        }

        /**
         * @brief Checks if every diffrence is bigger than MIN_DIFF
         * @param v compared dMatrixSqe
         * @return true if is bigger 
         * @return false if is less
         */
        bool operator!=(const dMatrixSqr &v) const{
            for (std::size_t i = 0; i < dim; ++i)
                for (std::size_t j = 0; j < dim; ++j)
                    if (abs(this->vector[i][j] - v[i][j]) <= MIN_DIFF)
                        return false;
            return true;
        }

        /**
         * @brief Checks if every value is lower than MIN_DIFF
         * @param v compared dMatrixSqe
         * @return true if is lower
         * @return false if is bigger 
         */
        bool operator!() const{
            for (std::size_t i = 0; i < dim; ++i)
                for (std::size_t j = 0; j < dim; ++j)
                    if (abs(this->vector[i][j]) >= MIN_DIFF)
                        return false;
            return true;
        }
};

/**
 * @brief four dimentional square double Matrix
 */
typedef dMatrixSqr<4> Matrix4x4;

/**
 * @brief three dimentional square double Matrix
 */
typedef dMatrixSqr<3> Matrix3x3;

/**
 * @brief two dimentional square double Matrix
 */
typedef dMatrixSqr<2> Matrix2x2;



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
         * @brief Construct a new Matrix Rot object and copy 
         * @param M Copieied Matrix
         */
        MatrixRot(const Matrix<double, 3, 3> &M):  Matrix3x3(M){}

        /**
         * @brief Construct a new Matrix Rot object and fill with rotating values
         * @param angle angle of rotation
         * @param axis of rotation ex. \p VectorZ , \p VectorX , \p VectorY
         */
        MatrixRot(double angle, const Vector3 &axis);
};

#endif // __MATRIXROT_H__