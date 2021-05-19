#include "doctest.h"
#include "Scene.hpp"

#include <limits>
extern bool DISPLAY;

TEST_CASE("1. Scene constructor"){
    CHECK_NOTHROW(Scene scene);
}

TEST_CASE("2. Draw Rectangle"){
    Scene scene;
    Object rect("prostokat.dat");

    CHECK_NOTHROW(scene.AddObject(rect));

   if(DISPLAY){
        scene.Update();
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
    }
  
}

TEST_CASE("3 Pointners to objects"){
    Scene scene;
    scene.AddObject(Object("line.dat"));

    scene[0].Rotate(90, VectorZ);

    CHECK( scene[0][0]  == Vector3({0, 100, 0}));
}

// TEST_CASE("4. Draw gravitation"){
//     Scene scene;
//     Object cuboid("cube.dat", 16);
//     CHECK_NOTHROW(scene.AddObject(&cuboid));

//     if(DISPLAY){
//         scene.Update();
//         std::cout << scene[0] << std::endl;
//         std::cout << "Press Enter to continue..." << std::endl;
//         std::cin.ignore(std::numeric_limits<int>().max(), '\n');
//     }
// }
