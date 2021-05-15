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
    std::cout << std::endl << std::endl << std::endl;

    Object *obj = new Object("cuboid.dat", 20);
    Scene scene;
    scene.AddObject(*obj);

    auto translate = new Vector3;
    auto rotation  = new MatrixRot;

    Menu menu({
        {"Rotate - Choose axis, angle and rotate times.", [&obj, &rotation](){
            char axis = ' ';
            double angle = 0, times = 0;
            try{
                std::cin >> axis >> angle >> times;
                if(!std::cin)
                    throw std::logic_error("Wrong input!!!");
                switch (axis){
                case 'x':
                    *rotation *= MatrixRot(angle, VectorX);
                    obj->Rotate(angle, times, VectorX);
                    break;
                case 'y':
                    *rotation *= MatrixRot(angle, VectorY);
                    obj->Rotate(angle, times, VectorY);
                    break;
                case 'z':
                    *rotation *= MatrixRot(angle, VectorZ);
                    obj->Rotate(angle, times, VectorZ);
                    break;
                default:
                    throw std::logic_error("Wrong axis");
                    break;
                }

            }
            catch(std::logic_error &e){
                std::cout << e.what() << std::endl;
            }
        }},
        {"Translate - vector x y z", [&obj, &translate](){
            Vector3 x;
            std::cin >> x;
            obj->Translate(x);
        }}
    });


    

    while(true){ 
        scene.Update();
        system("clear");
        std::cout << menu;
        try{
            std::cin >> menu;
        }
        catch(std::logic_error &e){
            std::cout << e.what() << std::endl;
        }
       
    }
    delete obj;
}