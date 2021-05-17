#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__
#include "Matrix3x3.hpp"
#include <iostream>
#include <string>
#include <vector>
/**
 * @file
 * Describes Transform Class and Object Class
 */

/**
 * @brief Collects position, angles and scale of whole object. 
 */
struct Transform{
    public:
        /**
         * @brief Pinned Transform
         */
        Transform *pinned;

        /**
         * @brief Center position
         */
        Vector3 position;

        /**
         * @brief Rotation 
         */
        MatrixRot rotation;

        /**
         * @brief Scale
         */
        Vector3 scale;

        /**
         * @brief Construct a new Transform object
         */
        Transform(){
            pinned = nullptr;
            position    = Vector3();
            rotation    = MatrixRot();
            scale       = Vector3({1, 1, 1});
        }
};


/**
 * @brief Object Class, base class for printed activeObjects on screen
 */
class Object: public Transform{
    private:
        /**
         * @brief Name of Object
         */
        std::string name;

        /**
         * @brief List of actualPoints of Object
         */
        std::vector<Vector3> actualPoints;

        /**
         * @brief List of origin points
         */
        std::vector<Vector3> originPoints;

    public:
        /**
         * @brief Construct a new Object object
         * @param name of Object
         * @param pointNumber how many actualPoints is in the reading file
         * @param centerPosition center position of object
         */
        Object(const std::string name, const std::size_t &vertexes, const Vector3 &centerPosition = Vector3());

        /**
         * @brief Construct a new Object object
         * @param obj copied Object
         */
        Object(const Object &obj);

        /**
         * @brief Destroy the Object object 
         */
        virtual ~Object();
        
        // /**
        //  * @brief Informations about position of center point, rotation, scale and pinned transform
        //  */
        // Transform transform;

        /**
         * @brief Acces function for name of Object
         * @return std::string name of Object
         */
        std::string Name() const { return this->name; }

        /**
         * @brief Counts number of actualPoints
         * @return std::size_t quantity of actualPoints
         */
        std::size_t CountPoints() const {return this->actualPoints.size();}

        /**
         * @brief Acces function for reading every actualPoints
         * @param index of point in \a actualPoints
         * @return Vector3 point
         */
        Vector3 operator[](const std::size_t &index) const;

        /**
         * @brief Acces function for writing every actualPoints
         * @param index of point in \a actualPoints
         * @return Vector3 point
         */
        Vector3 &operator[](const std::size_t &index);

        // /**
        //  * @brief Copies all actualPoints and name to this
        //  * @param obj copied object
        //  * @return Object& 
        //  */
        // Object &operator=(const Object &obj);

        /**
         * @brief Save actualPoints into file name
         */
        void Save();

        /**
         * @brief Translates every point from \a actualPoints and \a transform of Object
         * @param v translate Vector3
         */
        virtual void Translate(const Vector3 &v = Vector3());

        
        /**
         * @brief Rotates every point from \a actualPoints and \a transform of Object
         * @param angle angle of rotation
         * @param times how many rotate Object
         * @param v Vector3 of axis rotation
         */
        virtual void Rotate(const double &angle, const Vector3 &v);

        /**
         * @brief Rotates every point from \a actualPoints and \a transform of Object
         * @param M rotation matrix
         */
        virtual void Rotate(const MatrixRot &M = MatrixRot());

        std::vector<Vector3> OriginPoints() const;
};


/**
 * @brief Writing all \a actualPoints to \a Object 
 * @param strm input stream
 * @param object written \a Object
 * @return std::istream& 
 */
std::istream &operator>>(std::istream &strm, Object &object);


/**
 * @brief Printing all \a actualPoints from \a Object 
 * @param strm output stream
 * @param object printed \a Object
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &strm, const Object &object);

#endif // __OBJECT_HPP__