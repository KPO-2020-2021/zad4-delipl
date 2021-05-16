#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include "config.hpp"
#include "Object.hpp"
#include "GnuPlotApi.hpp"
#include <vector>
/**
 * @file Describes Scene Class
 */

/**
 * @brief class has Objects and can manipulate and display them on screen
 */
class Scene: public PzG::LaczeDoGNUPlota{
    /**
     * @brief std::vector of pointners to objects on Scene
     */
    std::vector<Object*> activeObjects;

    public:
        /**
         * @brief Construct a new Scene object and creates new GnuPlot window
         */
        Scene();

        /**
         * @brief Destroy the Scene object and all objects on Scene and kilall Gnuplot
         */
        ~Scene();

        /**
         * @brief Links existing Object to Scene
         * @param obj Object
         */
        void AddObject(Object *obj);

        /**
         * @brief Apply all moving functions to Objects
         */
        void Update();

        /**
         * @brief Access funtion to objects
         * @param i index of object
         * @return Object** 
         */
        Object** operator[](const std::size_t &i);
};
#endif // __SCENE_HPP__