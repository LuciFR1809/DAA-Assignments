/**
 * @file point.hpp
 * @brief Header file defining the class Point
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef POINT_HPP
#define POINT_HPP

/// Class to represent points
class Point
{
public:
    /// Point object is represented as (x, y)
    double x;
    /// Point object is represented as (x, y)
    double y;

    /**
     * @brief Default constructor.
     */
    Point() {}

    /**
     * @brief Constructor accepting @a x - x-coordinate and @a y - y-coordinate of the point
     * @param[in] x double
     * @param[in] y double
     */
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif