#include "doctest.h"
#include <fstream>
#include "Object.hpp"
TEST_CASE("1. Transform constructor"){
    CHECK_NOTHROW(Transform trans);
    Transform trans;
    CHECK(trans.position == Vector3());
    CHECK(trans.angles == Vector3());
    CHECK(trans.scale == Vector3({1, 1, 1}));
}
TEST_CASE("2. Object constriuctor, open file and read data"){
    CHECK_NOTHROW(Object rect("prostokat.dat", 4));
    Object rect("prostokat.dat", 4);

    CHECK(rect.Name() == "prostokat.dat");
    CHECK(rect.CountPoints() == 4);

    CHECK(rect[0] == Vector3({60, 60, 60}));
    CHECK(rect[1] == Vector3({210, 60, 60}));
    CHECK(rect[2] == Vector3({210, 160, 60}));
    CHECK(rect[3] == Vector3({60, 160, 60}));
    CHECK_THROWS(rect[4] == Vector3());

    CHECK_NOTHROW(rect.Save());
    CHECK_THROWS_AS(Object rect("nonExistsFile.dat", 4), std::exception);

    Object rect2(rect);
    CHECK(rect2[0] == Vector3({60, 60, 60}));
    CHECK(rect2[1] == Vector3({210, 60, 60}));
    CHECK(rect2[2] == Vector3({210, 160, 60}));
    CHECK(rect2[3] == Vector3({60, 160, 60}));
}


TEST_CASE("4. Object 8 points rotate"){
    CHECK_NOTHROW(Object rect("prostopadloscian.dat", 8));
    Object rect("prostokat.dat", 4);

    rect.Rotate(90, 1, VectorZ);
    CHECK(rect[0][0] - (-60) < MIN_DIFF);
    CHECK(rect[0][1] - (60) < MIN_DIFF);
    CHECK(rect[0][2] - (60) < MIN_DIFF);

    Object rect1("prostokat.dat", 4);
    rect1.Rotate(90, 1, VectorX);
    CHECK(rect1[0][0] - (60) < MIN_DIFF);
    CHECK(rect1[0][1] - (-60) < MIN_DIFF);
    CHECK(rect1[0][2] - (60) < MIN_DIFF);

    Object rect2("prostokat.dat", 4);
    MatrixRot D(90, VectorX);
    rect2.Rotate(D);
    CHECK(rect2[0][0] - (60) < MIN_DIFF);
    CHECK(rect2[0][1] - (-60) < MIN_DIFF);
    CHECK(rect2[0][2] - (60) < MIN_DIFF);
}