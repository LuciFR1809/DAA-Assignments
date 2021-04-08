/**
 * @file functions.hpp
 * @brief Header file for including functions required to find the segments for given set of input points
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include <vector>
#include "line.hpp"

using namespace std;

/**
 * @brief Slices out indices from @a i to @a j from the vector of points @a P 
 * @param[in] i integer, starting index
 * @param[in] j integer, ending index
 * @param[in] P vector of points, the array from where @a i to @a j elements will be sliced from
 * @return @a result vector of points, the sliced out vector of points
 * @note the original vector @a P remains unchanged during this process
*/
vector<Point> slice(int i, int j, vector<Point> P);

/**
 * @brief Gives the cumulative error of the calculated line for the given point set, Line is calculated by the normal formula 
 * @param[in] P vector of Points
 * @return @a error
*/
double cal_err(vector<Point> P);

/**
 * @brief It is the recursive function which calculates the penalty at each index 
 * @param[in] j integer, gives the index for which we wish to find penalty
 * @param[in] cost integer constant
 * @param[out] M vector of double which calculates minimum penalty at any given index 
 * @param[in] Err vector of vector of double, gives the error for different segments
 * @note @a M is given as the output, that is, it is calculated for index @a j
*/
void OPT(int j, double cost, vector<double> &M, vector<vector<double>> Err);

/**
 * @brief Driver function for @a OPT and also calculates error for all possible (start, end) pairs
 * @param[in] P vector of points, given input
 * @param[in] cost double, constant cost
 * @param[out] M vector of double, stores the penalty of every index
 * @param[out] Err vector of vector of double, stores the error values corresponding to every ( @a i, @a j ) pairs 
 * @note @a M and @a Err are the outputs for the functions. Err[i][j] for any given i and j refers to the error a segment starting from point on i-th index upto point on (i+j+1)-th index gets.
*/
void Segmented_Least_Square(vector<Point> P, double cost, vector<double> &M, vector<vector<double>> &Err);

/**
 * @brief recursively finds the best possible partitions of points, given @a M penalty at each index, @a P input point set, @a Err error for all possible segments of points
 * @param[in] j integer, partitions have to be found for elements lying before this index
 * @param[in] P vector of points, given input
 * @param[in] M vector of double, stores the penalty of every index
 * @param[in] cost double, constant cost
 * @param[in] Err vector of vector of double, stores the error values corresponding to every ( @a i, @a j ) pairs 
 * @param[out] result vector of vector of points, gives the final optimal partitions for the set of points
 * @note @a result gives a vector of partitions where each partition is a vector of points belonging to the same partition.
*/
void Find_Segment(int j, vector<Point> P, vector<double> M, double cost, vector<vector<double>> Err, vector<vector<Point>> &result);

#endif