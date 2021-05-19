#include "config.hpp"
#include "Object.hpp"
#include <fstream>
std::size_t Object::HMO = 0;

Object::Object(const std::string name, const Vector3 &centerPosition,
               const Vector3 &scale)
    : Transform() {
    this->lenPointsPack = 0;
    this->scale = scale;
    
    std::ifstream readFile(DATA_FOLDER + name);
    if(readFile.good())
        readFile >> *this;
    else{
        system("pwd");
        throw std::logic_error("Cannot read object file! " + std::string(DATA_FOLDER) + name);
    }
    readFile.close();
    std::cout   << "Loaded " << this->CountPoints() << " actualPoints " 
                << "from " << DATA_FOLDER  + name <<std::endl;

    for(auto &point : this->actualPoints)
        point += centerPosition;

    this->originPoints = std::vector<Vector3>(this->actualPoints.size(), Vector3());
    this->originPoints = this->actualPoints;

    this->Save();
    this->id = this->HMO++;
    this->name = std::to_string(this->id) + "_" + name;
}

Object::Object(const Object &obj) {
    this->actualPoints.clear();
    this->originPoints.clear();
    this->actualPoints = std::vector<Vector3>(obj.CountPoints(), Vector3());
    this->originPoints = std::vector<Vector3>(obj.CountPoints(), Vector3());

    this->name = obj.Name();
    this->lenPointsPack = obj.LengthOfPointPack();
    this->rotation = obj.rotation;
    this->scale = obj.scale;
    this->position = obj.position;

    this->originPoints = obj.OriginPoints();
    for(std::size_t i = 0; i < obj.CountPoints(); ++i){
        this->actualPoints[i] = obj[i];
    }
    this->Save();
    
    this->id = HMO++;
}
Object::~Object() {
    this->actualPoints.clear();
    --this->HMO;
}

Vector3 & Object::operator[](const std::size_t &index) { 
    if(index >= this->actualPoints.size())
        throw std::overflow_error("Vector overflow!");
    return this->actualPoints[index];
}   
Vector3 Object::operator[](const std::size_t &index) const{ 
    if(index >= this->actualPoints.size())
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
    object.actualPoints.clear();
    std::size_t onePack = 0;
    while (!strm.eof()){
        if (strm.peek() == '#') {
            strm.get();
        } 
        else if (strm.peek() == '\n') {
            strm.get();
            if (strm.peek() == '\n'){
                object.lenPointsPack = onePack;
            }
        }

        Vector3 x;
        try{
            strm >> x;
        }
        catch(std::logic_error &e){
            strm.clear();
            return strm;
            
        }

        if(!strm)
            throw std::logic_error("Cannot read Object!");

        for(std::size_t j = 0; j < 3; ++j)
            x[j] = x[j] * object.scale[j];

        object.actualPoints.push_back(x);

        if(object.lenPointsPack == 0)
            ++onePack;
    }
    return strm;
}


std::ostream &operator<<(std::ostream &strm, const Object &object){
    std::size_t k = 1;
    for(std::size_t i = 0; i < object.CountPoints(); ++i){
        for(std::size_t j = 0; j < 3; ++j)
            object[i][j] = object[i][j] / object.scale[j];

        strm << object[i] << std::endl;
        if(k == object.LengthOfPointPack()) {
            strm << "#\n\n";
            k = 0;
        }
        if(!strm)
            throw std::logic_error("Cannot read Object!");
        ++k;
    }
    return strm;
}