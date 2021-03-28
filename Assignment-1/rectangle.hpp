/**
 * @file rectangle.hpp
 * Header file for including Rectangle class
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "coord.hpp"
#include "interval.hpp"
#include "point.hpp"

/// Class representing physical rectangles
class Rectangle
{
public:
    /// Defines Rectangle using 4 coordinates (x_left, x_right, y_top, y_bottom).
    coord x_left;
    /// Defines Rectangle using 4 coordinates (x_left, x_right, y_top, y_bottom).
    coord x_right;
    /// Defines Rectangle using 4 coordinates (x_left, x_right, y_top, y_bottom).
    coord y_top;
    /// Defines Rectangle using 4 coordinates (x_left, x_right, y_top, y_bottom).
    coord y_bottom;

    /// Defines Rectangle using 2 Intervals (x_interval, y_interval).
    Interval x_interval;
    /// Defines Rectangle using 2 Intervals (x_interval, y_interval).
    Interval y_interval;

    /// Defines Rectangle using 4 points (top_left, top_right, bottom_left, bottom_right).
    Point top_left;
    /// Defines Rectangle using 4 points (top_left, top_right, bottom_left, bottom_right).
    Point top_right;
    /// Defines Rectangle using 4 points (top_left, top_right, bottom_left, bottom_right).
    Point bottom_left;
    /// Defines Rectangle using 4 points (top_left, top_right, bottom_left, bottom_right).
    Point bottom_right;

    /**
     * @brief Default Constructor.
     */
    Rectangle() {}

    /**
     * @brief Constructor to initialize rectangle using four coordinates
     * @param[in] x_left left coordinate
     * @param[in] x_right right coordinate
     * @param[in] y_top top coordinate
     * @param[in] y_bottom bottom coordinate
     */
    Rectangle(coord x_left, coord x_right, coord y_top, coord y_bottom)
    {
        this->x_left = x_left;
        this->x_right = x_right;
        this->y_top = y_top;
        this->y_bottom = y_bottom;

        this->x_interval = Interval(x_left, x_right);
        this->y_interval = Interval(y_bottom, y_top);

        this->top_left = Point(x_left, y_top);
        this->top_right = Point(x_right, y_top);
        this->bottom_left = Point(x_left, y_bottom);
        this->bottom_right = Point(x_right, y_bottom);
    }

    /**
     * @brief Constructor to initialize rectangle using two intervals
     * @param[in] x_interval interval along x-axis
     * @param[in] y_interval interval along y-axis
     */
    Rectangle(Interval x_interval, Interval y_interval)
    {
        this->x_interval = x_interval;
        this->y_interval = y_interval;

        this->x_left = x_interval.lower;
        this->x_right = x_interval.upper;
        this->y_top = y_interval.upper;
        this->y_bottom = y_interval.lower;

        this->top_left = Point(x_left, y_top);
        this->top_right = Point(x_right, y_top);
        this->bottom_left = Point(x_left, y_bottom);
        this->bottom_right = Point(x_right, y_bottom);
    }

    /**
     * @brief Constructor to initialize rectangle using four points
     * @param[in] top_left top-left point
     * @param[in] top_right top-right point
     * @param[in] bottom_left bottom-left point
     * @param[in] bottom_right bottom-right point
     */
    Rectangle(Point top_left, Point top_right, Point bottom_left, Point bottom_right)
    {
        this->top_left = top_left;
        this->top_right = top_right;
        this->bottom_left = bottom_left;
        this->bottom_right = bottom_right;

        this->x_left = top_left.x;
        this->x_right = top_right.x;
        this->y_top = top_left.y;
        this->y_bottom = bottom_left.y;

        this->x_interval = Interval(x_left, x_right);
        this->y_interval = Interval(y_bottom, y_top);
    }

    /**
     * @brief Compares two Rectangle objects.
     * @return @a true if rectangles are same, else @a false
     */
    bool operator==(const Rectangle &R) const
    {
        return this->x_left == R.x_left && this->x_right == R.x_right && this->y_top == R.y_top && this->y_bottom == R.y_bottom;
    }

    /**
     * @brief Compares two Rectangle objects.
     * @return @a true if rectangles are different, else @a false
     */
    bool operator!=(const Rectangle &R) const
    {
        return this->x_left != R.x_left || this->x_right != R.x_right || this->y_top != R.y_top || this->y_bottom != R.y_bottom;
    }

    /**
     * @brief Function to order the Rectangle objects.
        * Priority for ordering - @a x_left > @a y_bottom > @a x_right > @a y_top
     * @return @a true if first rectangle < second rectangle, else @a false
     */
    bool operator<(const Rectangle &R) const
    {
        return this->x_left != R.x_left       ? this->x_left < R.x_left
               : this->y_bottom != R.y_bottom ? this->y_bottom < R.y_bottom
               : this->x_right != R.x_right   ? this->x_right < R.x_right
                                              : this->y_top < R.y_top;
    }
};

#endif