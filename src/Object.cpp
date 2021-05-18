#include "config.hpp"
#include "Object.hpp"
#include <fstream>

Object::Object(const std::string name, const std::size_t &vertexes, const Vector3 &centerPosition): Transform(){
    this->name = name;
    this->actualPoints = std::vector<Vector3>(vertexes, Vector3());
    this->originPoints = std::vector<Vector3>(vertexes, Vector3());


    std::ifstream readFile(DATA_FOLDER + this->Name());
    if(readFile.good())
        readFile >> *this;
    else
        throw std::logic_error("Cannot read object file! "+ std::string(DATA_FOLDER) + this->Name());
    readFile.close();
    std::cout   << "Loaded " << this->CountPoints() << " actualPoints " 
                << "from " << DATA_FOLDER  + this->Name() <<std::endl;

    this->originPoints = this->actualPoints;

    this->Translate(centerPosition);
    this->Save();
}

Object::Object(const Object &obj) {
    this->actualPoints.clear();
    this->originPoints.clear();
    this->actualPoints = std::vector<Vector3>(obj.CountPoints(), Vector3());
    this->originPoints = std::vector<Vector3>(obj.CountPoints(), Vector3());

    this->name = obj.Name();
    this->rotation = obj.rotation;
    this->scale = obj.scale;
    this->position = obj.position;

    this->originPoints = obj.OriginPoints();
    for(std::size_t i = 0; i < obj.CountPoints(); ++i){
        this->actualPoints[i] = obj[i];
    }
    this->Save();
}

Object::~Object() {
    this->actualPoints.clear();
}

// Object& Object::operator=(const Object &obj) {
//     this->name = obj.Name();
//     this->actualPoints.clear();
//     this->actualPoints = std::vector<Vector3>(obj.CountPoints(), Vector3());
//     this->transform = obj.transform;

//     for(std::size_t i = 0; i < obj.CountPoints(); ++i){
//         this->actualPoints[i] = obj[i];
//     }

//     this->originPoints.clear();
//     this->originPoints = this->actualPoints();
//     this->Save();
//     return *this;
// }

Vector3 & Object::operator[](const std::size_t &index) { 
    if(index >= this->CountPoints())
        throw std::overflow_error("Vector overflow!");
    return this->actualPoints[index];
}   
Vector3 Object::operator[](const std::size_t &index) const{ 
    if(index >= this->CountPoints())
        throw std::overflow_error("Vector overflow!");
    return this->actualPoints[index];
}

void Object::Save(){
    std::ofstream tmpFile(TMP_FOLDER + this->Name());
    if(tmpFile)
        tmpFile << *this;
    tmpFile.close();
}

void Object::Translate(const Vector3 &v) {
    if(v != Vector3())
        this->position += v;

    this->actualPoints = this->originPoints;
    for(auto &x : this->actualPoints)
        x += position;
}

void Object::Rotate(const double &angle, const Vector3 &v) {
    MatrixRot rotM(angle, v);
    this->rotation = rotM * this->rotation;

    this->actualPoints = this->originPoints;
    for(auto &x: this->actualPoints)
        x = this->rotation * x;
}

void Object::Rotate(const MatrixRot &M) {
    this->rotation = M * this->rotation;

    this->actualPoints = this->originPoints;
    for(auto &x: this->actualPoints)
        x = this->rotation * x ;
}

std::vector<Vector3> Object::OriginPoints() const{
    return this->originPoints;
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
            object[i][j] = object[i][j] * object.scale[j];
    }
    return strm;
}


std::ostream &operator<<(std::ostream &strm, const Object &object){
    int k = 1;
    for(std::size_t i = 0; i < object.CountPoints(); ++i){
        for(std::size_t j = 0; j < 3; ++j)
            object[i][j] = object[i][j] / object.scale[j];

        strm << object[i] << std::endl;
        if(k % 4 == 0) strm << "#\n\n";
        if(!strm)
            throw std::logic_error("Cannot read Object!");
        ++k;
    }
    return strm;
}