#include "con.hpp"
template<>
Test<float, 2>::Test(){
    std::cout << "TEST FLOAT 2\n";
}

template<int x>
Test<double, x>::Test(){
    std::cout << "TEST ONE TEMPLATE\n";
}