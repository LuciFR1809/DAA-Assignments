/**
 * @file edge.hpp
 * Header file for including Edge class
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef EDGE_HPP
#define EDGE_HPP

#include "coord.hpp"
#include "interval.hpp"

/// Enumeration EdgeType{left_edge, bottom_edge, right_edge, top_edge} is used in Edge
enum EdgeType
{
    left_edge,
    bottom_edge,
    right_edge,
    top_edge
};

/// Edge object is used for creating Rectangle
class Edge
{
public:
    /// Common coordinate of the endpoints
    coord cord;
    /// Interval by which the edge spans
    Interval interval;
    /// Stores which side the edge is present
    EdgeType side;

    /**
     * @brief Default Constructor.
     */
    Edge() {}

    /**
     * @brief Constructor accepting four parameters.
     * @param[in] x common coordinate of edge
     * @param[in] y_top second endpoint of @a interval
     * @param[in] y_bottom first endpoint of @a interval
     * @param[in] side side of rectangle
     */
    Edge(coord x, coord y_top, coord y_bottom, EdgeType side)
    {
        this->cord = x;
        this->interval = Interval(y_bottom, y_top);
        this->side = side;
    }

    /**
     * @brief Compares two Edge objects.
     * @return @a true if edges are same, else @a false
     */
    bool operator==(const Edge &E) const
    {
        return this->cord == E.cord && this->interval == E.interval && this->side == E.side;
    }

    /**
     * @brief Compares two Edge objects.
     * @return @a true if edges are different, else @a false
     */
    bool operator!=(const Edge &E) const
    {
        return this->cord != E.cord || this->interval != E.interval || this->side != E.side;
    }

    /**
     * @brief Function to order the Edge objects.
        * Priority for ordering - @a cord > @a interval > @a side
     * @return @a true if first edge < second edge, else @a false
     */
    bool operator<(const Edge &E) const
    {
        return this->cord != E.cord			  ? this->cord < E.cord
               : this->interval != E.interval ? this->interval < E.interval
                                              : this->side < E.side;
    }
};

#endif