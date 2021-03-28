/**
 * @file methods_measure.hpp
 * Header file for including function required to find the measure for given set of input rectangles
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef MEASURE_CPP
#define MEASURE_CPP

#include <algorithm>
#include <cmath>
#include <set>

#include "coord.hpp"
#include "ctree.hpp"
#include "edge.hpp"
#include "interval.hpp"
#include "line_segment.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "stripe.hpp"

#include "methods_contour.hpp"

using namespace std;

/**
 * @brief Function to find consecutive y_intervals given a set of y coordinates. Used to find the y_intervals of Stripes
 * @param[in] Y parameter set of Coord 
 * @return set of consecutive y-intervals
*/
set<Interval> partition(set<coord> Y);

/**
 * @brief Driver function for the main divide and conquer function STRIPES, returns a set of stripes with x_measure giving the length of x-interval occupied by set of input rectangles 
 * @param[in] Rect set of Rectangle
 * @param[out] S set of StripeMeasure
 * @see STRIPES()
 * @note since set of StripeMeasure is passed by reference, although the return type is void, the function gives @a S as a result
*/
void RECTANGLE_DAC(set<Rectangle> Rect, set<StripeMeasure> &S);

/**
 * @brief Function to perform the divide and conquer algorithm given a set of left and right edges and a x-interval, It gives four outputs as a result which are set of intervals for only left edges @a L, set of intervals for only right edges @a R, set of coord @a P and the set of StripeMeasure @a S
 * @param[in] V set of Edge
 * @param[in] x_ext Interval
 * @param[out] L set of Interval
 * @param[out] R set of Interval
 * @param[out] P set of Coord 
 * @param[out] S set of StripeMeasure
 * @note although the return type is void, the function returns @a L, @a R, @a P, @a S since they are passed by reference
*/
void STRIPES(set<Edge> V, Interval x_ext, set<Interval> &L, set<Interval> &R, set<coord> &P, set<StripeMeasure> &S);

/**
 * @brief Function to copy the set of Y-intervals of StripeMeasure of two partitions of divide algorithm into each other, to make the y-intervals of both partitions uniform
 * @param[in] S set of StripeMeasure
 * @param[in] P set of Coord 
 * @param[in] x_int Interval
 * @return set of StripeMeasure
 * @see Interval::isSupersetOf()
*/
set<StripeMeasure> copy(set<StripeMeasure> S, set<coord> P, Interval x_int);

/**
 * @brief Function to find left and right edges such that their partners don't exist in the same set 
 * @param[in, out] S set of StripeMeasure
 * @param[in] J set of Interval
 * @see Interval::isSupersetOf()
 * @see partition()
 * @note although the return type is void, the function returns @a S , since it is passed by reference, where edges whose partners are present in same stripe are removed
*/
void blacken(set<StripeMeasure> &S, set<Interval> J);

/**
 * @brief Function to perform the concatenation operation of two x-partitions with same y-interval
 * @param[in] S1 set of StripeMeasure
 * @param[in] S2 set of StripeMeasure
 * @param[in] P set of coord
 * @param[in] x_int Interval
 * @return @a S_new new set of StripeMeasure after concatenation
 * @see partition()
*/
set<StripeMeasure> concat(set<StripeMeasure> S1, set<StripeMeasure> S2, set<coord> P, Interval x_int);

/**
 * @brief Function computes the measure of union of set of rectangles using the output StripeMeasure from @a RECTANGLE_DAC function
 * @param[in] S set of StripeMeasure
 * @return double value giving area of union of set of rectangles  
*/
double measure(set<StripeMeasure> S);

#endif