#include "doctest.h"
#include "Quaternion.hpp"

TEST_CASE("1. Quaternion constructors"){
    CHECK_NOTHROW(Quaternion Kwa(Vector3({1.0, 1.0, 1.0}), 90));
}
TEST_CASE("2. Rotate by quaternion"){
    Quaternion Kwa(VectorZ, 90);
    Vector3 v({100.0, 200.0, 0.0});

    v = Kwa*v;
    CHECK(v[0] == 200);
    CHECK(v[1] == -100);
    CHECK(v[2] == 0);
}