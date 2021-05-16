#include <iostream>
#include <limits>
#include "config.hpp"
#include "Menu.hpp"
#include "Scene.hpp"


int main(){
    std::cout << "Project Rotation 3D based on C++ Boiler Plate by Jakub Delicat v"
              << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
              << "."
              << PROJECT_VERSION_MINOR /* istotne zmiany */
              << "."
              << PROJECT_VERSION_PATCH /* naprawianie bugów */
              << "."
              << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
              << std::endl;
    std::system("cat ./LICENSE");
    std::cout << "Press enter to start..." << std::endl << std::endl << std::endl;
    std::cin.ignore(std::numeric_limits<int>().max(), '\n');

    Object ref("cuboid.dat", 20);
    Object obj(ref);

    Scene scene;
    scene.AddObject(&obj);

    Vector3 translation;
    // MatrixRot rotation;
    auto rotation = new MatrixRot;

    Menu menu({
        {"Rotate - Choose axis, angle and rotate times.", [&rotation](){
            char axis = ' ';
            double angle = 0, times = 0;
            try{
                std::cin >> axis >> angle >> times;
                if(!std::cin)
                    throw std::logic_error("Wrong input!!!");
                switch (axis){
                case 'x':
                    *rotation = (*rotation) * MatrixRot(angle, VectorX);
                    break;
                case 'y':
                    *rotation = (*rotation) * MatrixRot(angle, VectorY);
                    break;
                case 'z':
                    *rotation = (*rotation) * MatrixRot(angle, VectorZ);
                    break;
                default:
                    throw std::logic_error("Wrong axis");
                    break;
                }

            }
            catch(std::logic_error &e){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<int>().max(), '\n');
                std::cout << e.what() << std::endl;
                
            }
        }},
        {"Translate - vector x y z", [&translation](){
            Vector3 x;
            std::cin >> x;
            translation += x;
        }}
    });


    while(true){ 
     
        scene.Update();
        std::cout << menu;
        try{
            std::cin >> menu;
        }
        catch(std::logic_error &e){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>().max(), '\n');
            std::cout << e.what() << std::endl;
        }
        catch(...){
            return 0;
        }

        obj = ref;
        obj.Translate(translation);
        std::cout << *rotation;
        obj.Rotate(*rotation);
    }
}