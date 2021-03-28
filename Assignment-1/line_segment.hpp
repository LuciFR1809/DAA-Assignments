/**
 * @file line_segment.hpp
 * Header file for including LineSegment class
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

#include "coord.hpp"
#include "interval.hpp"

/// LineSegment object is used for contour calculation
class LineSegment
{
public:
    /// Interval by which the line segment spans
    Interval interval;
    /// Common coordinate of the endpoints
    coord cord;

    /**
     * @brief Default Constructor.
     */
    LineSegment() {}

    /**
     * @brief Constructor accepting two parameters.
     * @param[in] in Interval of line segment
     * @param[in] cord coordinate of line segment
     */
    LineSegment(Interval in, coord cord)
    {
        this->interval = in;
        this->cord = cord;
    }

    /**
     * @brief Compares two LineSegment objects.
     * @return @a true if line segments are same, else @a false
     */
    bool operator==(const LineSegment &L) const
    {
        return this->cord == L.cord && this->interval == L.interval;
    }

    /**
     * @brief Compares two LineSegment objects.
     * @return @a true if line segments are different, else @a false
     */
    bool operator!=(const LineSegment &L) const
    {
        return this->cord != L.cord || this->interval != L.interval;
    }

    /**
     * @brief Function to order the LineSegment objects.
        * Priority for ordering - @a cord > @a interval
     * @return @a true if first line segment < second line segment, else @a false
     */
    bool operator<(const LineSegment &L) const
    {
        return this->cord != L.cord ? this->cord < L.cord
                                    : this->interval < L.interval;
    }
};

#endif