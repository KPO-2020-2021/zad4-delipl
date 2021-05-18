#include "test.hpp"
template<typename T,int x>
Test<T, x>::Test(){
    std::cout<< "Constructor template\n";
}
template<typename T,int x>
Test<T, x>::Test(const Test &KK){
    std::cout<< "Constructor cop template\n";
    for(int i = 0; i < x; ++i)
        this->tab = T();
}
