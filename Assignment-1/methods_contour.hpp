/**
 * @file methods_contour.hpp
 * Header file for including functions required to find the contour for given set of input rectangles
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef CONTOUR_CPP
#define CONTOUR_CPP

#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>

#include "coord.hpp"
#include "ctree.hpp"
#include "edge.hpp"
#include "interval.hpp"
#include "line_segment.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "stripe.hpp"

#include "methods_measure.hpp"

using namespace std;

/**
 * @brief Driver function for the main divide and conquer function STRIPES, returns a set of stripes with tree data structure giving pieces of line segments beloning to rectangles in a stripe
 * @param[in] Rect set of Rectangle
 * @param[out] S set of StripeContour
 * @note since set of StripeContour is passed by reference, although the return type is void, the function gives @a S as a result
*/
void RECTANGLE_DAC(set<Rectangle> Rect, set<StripeContour> &S);

/**
 * @brief Function to perform the divide and conquer algorithm given a set of left and right edges and a x-interval, It gives four outputs as a result which are set of intervals for only left edges @a L, set of intervals for only right edges @a R, set of coord @a P and the set of StripeContour @a S
 * @param[in] V set of Edge
 * @param[in] x_ext Interval
 * @param[out] L set of Interval
 * @param[out] R set of Interval
 * @param[out] P set of Coord 
 * @param[out] S set of StripeContour
 * @note although the return type is void, the function returns @a L, @a R, @a P, @a S since they are passed by reference
*/
void STRIPES(set<Edge> V, Interval x_ext, set<Interval> &L, set<Interval> &R, set<coord> &P, set<StripeContour> &S);

/**
 * @brief Function to copy the set of Y-intervals of StripeContour of two partitions of divide algorithm into each other, to make the y-intervals of both partitions uniform
 * @param[in] S set of StripeContour
 * @param[in] P set of Coord 
 * @param[in] x_int Interval
 * @return set of StripeContour
*/
set<StripeContour> copy(set<StripeContour> S, set<coord> P, Interval x_int);

/**
 * @brief Function to find left and right edges such that their partners don't exist in the same set 
 * @param[in, out] S set of StripeContour
 * @param[in] J set of Interval
 * @note although the return type is void, the function returns @a S , since it is passed by reference, where edges whose partners are present in same stripe are removed
*/
void blacken(set<StripeContour> &S, set<Interval> J);

/**
 * @brief Function to perform the concatenation operation of two x-partitions with same y-interval
 * @param[in] S1 set of StripeContour
 * @param[in] S2 set of StripeContour
 * @param[in] P set of coord
 * @param[in] x_int Interval
 * @return set of StripeContour after concatenation
*/
set<StripeContour> concat(set<StripeContour> S1, set<StripeContour> S2, set<coord> P, Interval x_int);

/**
 * @brief Function to merge two or more overlapping linesegments
 * @param[in] L set of Line segment
 * @return set of line segment after merge operation
*/
set<LineSegment> postProcess(set<LineSegment> L);

/**
 * @brief Function used to traverse through Ctree
 * @param[in] C pointer to Ctree node
 * @param[out] start reference to vector of coord
 * @param[out] end reference to vector of coord
 * @note @a start and @a end are the output as they are passed by reference
*/
void traverseCtree(Ctree *C, vector<coord> &start, vector<coord> &end);

/**
 * @brief Function used to make intervals using coordinates contained in Ctree
 * @param[in] C pointer to Ctree node
 * @return set of Interval
 * @see traverseCtree
*/
set<Interval> getIntervals(Ctree *C);

/**
 * @brief Corresponding to given edge this function finds the contour pieces 
 * @param[in] h set of Edge
 * @param[in] S set of StripeContour
 * @return set of Line segment (contour lines)
*/
set<LineSegment> contour_pieces(Edge h, set<StripeContour> S);

/**
 * @brief Finds the set of Contour Pieces corresponding to all the edges in a set
 * @param[in] H set of Edge
 * @param[in] S set of StripeContour
 * @return set of Line segment (contour lines)
 * @see contour_pieces()
 * @see postProcess()
*/
set<LineSegment> contour(set<Edge> H, set<StripeContour> S);

#endif