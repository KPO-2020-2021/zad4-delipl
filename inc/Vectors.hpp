#ifndef __VECTORS_HPP__
#define __VECTORS_HPP__
#include <cstdlib>
#include "Vector.hpp"

/**
 * @file Instantiation of template class Vector
 */

#ifndef MIN_DIFF
    /**
     * @brief Minimal difference between two double numbers. It might be included from config.hpp
     */
    #define MIN_DIFF 0.000000001 
#endif // !MIN_DIFF

/**
 * @brief four dimentional double Vector
 */
typedef Vector<double, 4> Vector4;

/**
 * @brief three dimentional double Vector
 */
typedef Vector<double, 3> Vector3;

/**
 * @brief two dimentional double Vector
 */
typedef Vector<double, 2> Vector2;

/**
 * @brief X axis Vector3 (1, 0, 0)
 */
static Vector3 VectorX = {1, 0, 0};

/**
 * @brief Y axis Vector3 (0, 1, 0)
 */
static Vector3 VectorY = {0, 1, 0};

/**
 * @brief Z axis Vector3 (0, 0, 1)
 */
static Vector3 VectorZ = {0, 0, 1};

template<std::size_t dim>   
bool Vector<double, dim>::operator==(const Vector<double, dim> &v) const{
    for (std::size_t i = 0; i < dim; ++i)
        if (abs(this->cord[i] - v[i]) > MIN_DIFF)
            return false;
    return true;
}

template<std::size_t dim>  
bool Vector<double, dim>::operator!=(const Vector<double, dim> &v) const{
    for (std::size_t i = 0; i < dim; ++i)
        if (abs(this->cord[i] - v[i]) <= MIN_DIFF)
            return false;
    return true;
}

template<std::size_t dim>  
bool  Vector<double, dim>::operator!() const{
    for (double x: this->cord)
        if (x >= MIN_DIFF)
            return false;
    return true;
}

#endif // __VECTORS_HPP__