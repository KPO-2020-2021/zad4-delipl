#include "Matrixes.hpp"

MatrixRot::MatrixRot(): Matrix3x3() {
    for(std::size_t i = 0; i < 3; ++i)
        (*this)[i][i] = 1;
}

MatrixRot::MatrixRot(double angle, const Vector3 &axis){
    angle *= M_PI/180;
    if(axis == VectorX){
        (*this)[0] = Vector3({1.0, 0.0         , 0.0    });
        (*this)[1] = Vector3({0, cos(angle), -sin(angle)});
        (*this)[2] = Vector3({0, sin(angle),  cos(angle)});
    }
    else if(axis == VectorY){
        (*this)[0] = Vector3({cos(angle) , 0, sin(angle)});
        (*this)[1] = Vector3({0          , 1, 0         });
        (*this)[2] = Vector3({-sin(angle), 0, cos(angle)});
    }
    else if(axis == VectorZ){
        (*this)[0] = Vector3({cos(angle) , -sin(angle), 0});
        (*this)[1] = Vector3({sin(angle) , cos(angle), 0});
        (*this)[2] = Vector3({0          , 0         , 1});
    }   
    else{
        throw std::logic_error("Can't make MatrixRot. Wrong axis.");
    }
}

