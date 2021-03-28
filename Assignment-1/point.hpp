/**
 * @file point.hpp
 * Header file for including Point class
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef POINT_HPP
#define POINT_HPP

#include "coord.hpp"

/// Point object is used for creating Rectangle
class Point
{
public:
    /// x coordiante of point
    coord x;
    /// y coordiante of point
    coord y;

    /**
     * @brief Default constructor.
     */
    Point() {}

    /**
     * @brief Constructor accepting @a x and @a y coordinates.
     * @param[in] x x coordinate of point
     * @param[in] y y coordinate of point
     */
    Point(coord x, coord y)
    {
        this->x = x;
        this->y = y;
    }

    /**
     * @brief Compares two Point objects.
     * @return @a true if points are same, else @a false
     */
    bool operator==(const Point &P) const
    {
        return this->x == P.x && this->y == P.y;
    }

    /**
     * @brief Compares two Point objects.
     * @return @a true if points are different, else @a false
     */
    bool operator!=(const Point &P) const
    {
        return this->x != P.x || this->y != P.y;
    }

    /**
     * @brief Function to order the Point objects.
        * Priority for ordering - @a x > @a y
     * @return @a true if first point < second point, else @a false
     */
    bool operator<(const Point &P) const
    {
        return this->x != P.x ? this->x < P.x
                              : this->y < P.y;
    }
};

#endif