#ifndef __CON_HPP__
#define __CON_HPP__

#include "test.hpp"

template<>
Test<float, 2>::Test();
typedef Test<float, 2> Test2;



typedef Test<double, 4> dTest4;

#endif // __CON_HPP__