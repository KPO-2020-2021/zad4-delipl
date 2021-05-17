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
    MatrixRot rotation;

    /* -------------------------------------------------------------------------- */
    /*                              MENU CONSTRUCTOR                              */
    /* -------------------------------------------------------------------------- */
    bool finish = false;
    MatrixRot oneRot;
    Menu menu({
        {"Rotate - Choose axis, angle (print . to exit)", [&rotation, &oneRot](){
            char axis = ' ';
            double angle = 0;
            try{
                bool finish = false;
                std::vector<MatrixRot> rotationSequece;
                while(!finish){
                    
                    std::cin >> axis;
                    if(!std::cin)
                        throw std::logic_error("Wrong input!!!");

                    if(axis == '.'){
                        std::cout << "How many time rotate?" << std::endl;
                        std::size_t times;
                        std::cin >> times;
                        if(!std::cin)
                            throw std::logic_error("Wrong input!!!");

                        for(std::size_t i = 0; i < times; ++i)
                            for(auto &rot : rotationSequece)
                                rotation = rotation * rot;
                        
                        return;
                    }
                    
                    std::cin  >> angle;
                    if(!std::cin)
                        throw std::logic_error("Wrong input!!!");

                    switch (axis){
                    case 'X':
                    case 'x':
                        rotationSequece.push_back(MatrixRot(angle, VectorX));
                        break;
                    case 'Y':
                    case 'y':
                        rotationSequece.push_back(MatrixRot(angle, VectorY));
                        break;
                    case 'Z':
                    case 'z':
                        rotationSequece.push_back(MatrixRot(angle, VectorZ));
                        break;
                    default:
                        throw std::logic_error("Wrong axis");
                        break;
                    }
                }
            }
            catch(std::logic_error &e){
                std::cin.clear();
                // std::cin.ignore(std::numeric_limits<int>().max(), '\n');
                std::cout << e.what() << std::endl;
            }
        }},
        {"Rotate again with the last sequence", [&oneRot, &rotation](){
            rotation = rotation * oneRot;
        }},
        {"Print rotaion Matrix", [&rotation](){ std::cout << rotation << std::endl;}},
        {"Translate - vector x y z", [&translation](){
            Vector3 x;
            std::cin >> x;
            translation += x;
        }},
        {"Print cords of Figure", [&obj](){std::cout << obj << std::endl;}},
        {"Check lengths of Figure",[&obj](){
            std::cout << "Edge 1 a: " << (obj[1] - obj[2]).Length() << "\t";
            std::cout << "Edge 2 a: " << (obj[5] - obj[6]).Length() << "\t";
            std::cout << "Edge 3 a: " << (obj[9] - obj[10]).Length() << "\t";
            std::cout << "Edge 4 a: " << (obj[13] - obj[14]).Length() << "\t";
            std::cout << std::endl;

            std::cout << "Diffrence between edges: " << (obj[5] - obj[6]).Length() - (obj[9] - obj[10]).Length()<< "\t";
            std::cout << "Diffrence between edges: " << (obj[1] - obj[2]).Length() - (obj[13] - obj[14]).Length()<< "\t";
            std::cout << std::endl;
            std::cout << std::endl;

            std::cout << "Edge 1 b: " << (obj[1] - obj[5]).Length() << "\t";
            std::cout << "Edge 2 b: " << (obj[9] - obj[13]).Length() << "\t";
            std::cout << "Edge 3 b: " << (obj[2] - obj[6]).Length() << "\t";
            std::cout << "Edge 4 b: " << (obj[10] - obj[14]).Length() << "\t";
            std::cout << std::endl;

            std::cout << "Diffrence between edges: " << (obj[5] - obj[6]).Length() - (obj[9] - obj[10]).Length()<< "\t";
            std::cout << "Diffrence between edges: " << (obj[1] - obj[2]).Length() - (obj[13] - obj[14]).Length()<< "\t";
            std::cout << std::endl;
            std::cout << std::endl;
            
            std::cout << "Edge 1 c: " << (obj[5] - obj[9]).Length() << "\t";
            std::cout << "Edge 2 c: " << (obj[13] - obj[17]).Length() << "\t";
            std::cout << "Edge 3 c: " << (obj[6] - obj[10]).Length() << "\t";
            std::cout << "Edge 4 c: " << (obj[14] - obj[18]).Length() << "\t";
            std::cout << std::endl;

            std::cout << "Diffrence between edges: " << (obj[5] - obj[6]).Length() - (obj[9] - obj[10]).Length()<< "\t";
            std::cout << "Diffrence between edges: " << (obj[1] - obj[2]).Length() - (obj[13] - obj[14]).Length()<< "\t";
            std::cout << std::endl;
            std::cout << std::endl;

        }},
        {"Exit", [&finish](){
            finish = true;
        }}
    });

    /* -------------------------------------------------------------------------- */
    /*                                  MAIN LOOP                                 */
    /* -------------------------------------------------------------------------- */
    
    while(!finish){ 
     
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
        obj.Rotate(rotation);
    }
}