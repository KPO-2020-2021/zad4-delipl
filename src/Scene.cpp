#include "Scene.hpp"

Scene::Scene(){
    this->UsunWszystkieNazwyPlikow();
    this->_Xmax =  10 * WINDOW_SCALE;
    this->_Xmin = -10 * WINDOW_SCALE;
    this->_Ymax =  10  * WINDOW_SCALE;
    this->_Ymin = -10  * WINDOW_SCALE;
    this->_Zmax =  10  * WINDOW_SCALE;
    this->_Zmin =  -10 * WINDOW_SCALE;
    this->ZmienTrybRys(PzG::TR_3D);
    this->Inicjalizuj();

    this->activeObjects = std::vector<Object*>();
}

Scene::~Scene(){
    system("killall gnuplot");
}

void Scene::AddObject(Object *obj){
    this->DodajNazwePliku(std::string(TMP_FOLDER + obj->Name()).c_str());
    this->activeObjects.push_back(obj);
    std::cout << obj << "   " << this->activeObjects[0] << std::endl;
}

Object **Scene::operator[](const std::size_t &i){
    if(i >= this->activeObjects.size())
        throw std::overflow_error("There is no more objects");
    return &(this->activeObjects[i]);
}
        
void Scene::Update(){
    for(Object* obj : this->activeObjects){
        obj->Save();
    }
    this->Rysuj();
}

void Scene::Start(){

}