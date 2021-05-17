#include "config.hpp"
#include "Object.hpp"
#include <fstream>

Object::Object(const std::string name, const std::size_t &points){
    this->name = name;
    this->points = std::vector<Vector3>(points, Vector3());
    this->transform = Transform();

    std::ifstream readFile(DATA_FOLDER + this->Name());
    if(readFile.good())
        readFile >> *this;
    else
        throw std::logic_error("Cannot read object file! "+ std::string(DATA_FOLDER) + this->Name());
    readFile.close();
    std::cout   << "Loaded " << this->CountPoints() << " points " 
                << "from " << DATA_FOLDER  + this->Name() <<std::endl;
    
    this->Save();
}

Object::Object(const Object &obj) {
    this->name = obj.Name();
    this->points.clear();
    this->points = std::vector<Vector3>(obj.CountPoints(), Vector3());
    this->transform = obj.transform;

    for(std::size_t i = 0; i < obj.CountPoints(); ++i){
        this->points[i] = obj[i];
    }
    this->Save();
}

Object::~Object() {
    this->points.clear();
}

Object& Object::operator=(const Object &obj) {
    this->name = obj.Name();
    this->points.clear();
    this->points = std::vector<Vector3>(obj.CountPoints(), Vector3());
    this->transform = obj.transform;

    for(std::size_t i = 0; i < obj.CountPoints(); ++i){
        this->points[i] = obj[i];
    }
    this->Save();
    return *this;
}

Vector3 & Object::operator[](const std::size_t &index) { 
    if(index >= this->CountPoints())
        throw std::overflow_error("Vector overflow!");
    return this->points[index];
}   
Vector3 Object::operator[](const std::size_t &index) const{ 
    if(index >= this->CountPoints())
        throw std::overflow_error("Vector overflow!");
    return this->points[index];
}

void Object::Save(){
    std::ofstream tmpFile(TMP_FOLDER + this->Name());
    if(tmpFile)
        tmpFile << *this;
    tmpFile.close();
}

void Object::Translate(const Vector3 &v) {
    for(auto &x : this->points)
        x += v;
    transform.position += v;
}

void Object::Rotate(const double &angle, const std::size_t &times, const Vector3 &v) {
    MatrixRot rotM(angle, v);
    for (std::size_t t = 0; t < times; ++t)
        for(auto &x: this->points)
            x = rotM * x ;
    transform.rotation = transform.rotation * rotM;
}

void Object::Rotate(const MatrixRot &M) {
        for(auto &x: this->points)
            x = M * x ;
}

std::istream &operator>>(std::istream &strm, Object &object){
    char c = ' ';
    for(std::size_t i = 0; i < object.CountPoints(); ++i){
        c = ' ';
        strm >> c;
        if(c == '#')
            strm.ignore(std::numeric_limits<int>().max(), '\n');
        else
            strm.putback(c);
        strm >> object[i];
        if(!strm)
            throw std::logic_error("Cannot read Object!");

        for(std::size_t j = 0; j < 3; ++j)
            object[i][j] = object[i][j] * object.transform.scale[j];
    }
    return strm;
}


std::ostream &operator<<(std::ostream &strm, const Object &object){
    int k = 1;
    for(std::size_t i = 0; i < object.CountPoints(); ++i){
        for(std::size_t j = 0; j < 3; ++j)
            object[i][j] = object[i][j] / object.transform.scale[j];

        strm << object[i] << std::endl;
        if(k % 4 == 0) strm << "#\n\n";
        if(!strm)
            throw std::logic_error("Cannot read Object!");
        ++k;
    }
    return strm;
}