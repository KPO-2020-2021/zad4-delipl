#ifndef __TEST_HPP__
#define __TEST_HPP__
#include <iostream>
template<typename T,int x>
class Test{
    public:
        T tab[x];
        Test();
        Test(const Test &KK);
};
#include "test.tpp"
#endif // __TEST_HPP__