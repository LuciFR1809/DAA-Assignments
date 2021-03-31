/**
 * @file line.hpp
 * Header file defining the class line
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */


#ifndef LINE_HPP
#define LINE_HPP

#include <vector>
#include <math.h>
#include "point.hpp"

using namespace std;

class Line{
    public:
        
        /// Using y = a*x + b equation of line 
        double a, b;

        /**
        * @brief Default constructor.
        */
        
        Line(){}

        /**
        * @brief Constructor accepting parameters @a a - slope and @a b - y-intercept of the line
        * @param[in] a slope
        * @param[in] b y-intercept
        */

        Line(double a, double b){
            this->a = a;
            this->b = b;
        }

        /**
        * @brief Constructor accepting vector of Points @a P and finding best fit line through them
        * @param[in] P vector of Point
        */

        Line(vector <Point> P)
        {
            int n = P.size();
            double x_sum=0, y_sum=0, prod_sum=0, x_sq_sum=0;

            for (auto i : P)
            {
                x_sum += i.x;
                y_sum += i.y;
                x_sq_sum += (i.x*i.x);
                prod_sum += (i.y*i.x);
            }
            if(n*x_sq_sum - x_sum*x_sum == 0)
                this->a = INFINITY;
            else
                this->a = (n*prod_sum - x_sum*y_sum)/(n*x_sq_sum - x_sum*x_sum);
                
            this->b = (y_sum - a*x_sum)/n;
        }

        /**
        * @brief Function to find error of point @a P with Line .
        * @param[in] P Point
        * @return @a error 
        */
        double err(Point P){
            double s = P.y - a*P.x - b;
            return s*s;
        }
};

#endif