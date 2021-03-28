/**
 * @file stripe.hpp
 * Header file for including StripeContour and StripeMeasure classes
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef STRIPE_HPP
#define STRIPE_HPP

#include "ctree.hpp"
#include "interval.hpp"

/// Class representing stripe data structure for finding the contour for given set of input rectangles
class StripeContour
{
public:
    /// Defines StripeContour using two Interval objects and one pointer to ctree data (x_interval, y_interval, tree)
    Interval x_interval;
    /// Defines StripeContour using two Interval objects and one pointer to ctree data (x_interval, y_interval, tree)
    Interval y_interval;
    /// Defines StripeContour using two Interval objects and one pointer to ctree data (x_interval, y_interval, tree)
    Ctree *tree;

    /**
     * @brief Default Constructor.
     */
    StripeContour() {}

    /**
     * @brief Constructor to initialize stripe for contour function using x-interval, y-interval and pointer to ctree data structure
     * @param[in] x_interval x_interval of the stripe
     * @param[in] y_interval y_interval of the stripe
     * @param[in] tree pointer to c_tree data structure
     */
    StripeContour(Interval x_interval, Interval y_interval, Ctree *tree)
    {
        this->x_interval = x_interval;
        this->y_interval = y_interval;
        this->tree = tree;
    }

     /**
     * @brief Compares two StripeContour objects.
     * @return @a true if stripes are same, else @a false
     */
    bool operator==(const StripeContour &S) const
    {
        return this->x_interval == S.x_interval && this->y_interval == S.y_interval && this->tree == S.tree;
    }

    /**
     * @brief Compares two StripeContour objects.
     * @return @a true if stripes are different, else @a false
     */
    bool operator!=(const StripeContour &S) const
    {
        return this->x_interval != S.x_interval || this->y_interval != S.y_interval || this->tree != S.tree;
    }

    /**
     * @brief Compares two StripeContour objects.
        * Priority for ordering - @a x_interval > @a y_interval > @a tree
     * @return @a true if first StripeContour object < second StripeContour object, else @a false
     */
    bool operator<(const StripeContour &S) const
    {
        return this->x_interval != S.x_interval   ? this->x_interval < S.x_interval
               : this->y_interval != S.y_interval ? this->y_interval < S.y_interval
                                                  : this->tree < S.tree;
    }
};

///Class representing stripe data structure to find the measure for given set of input rectangles
class StripeMeasure
{
public:
    /// Defines StripeMeasure using two intervals and a real number (x_interval, y_interval, x_measure) 
    Interval x_interval;
    /// Defines StripeMeasure using two intervals and a real number (x_interval, y_interval, x_measure) 
    Interval y_interval;
    /// Defines StripeMeasure using two intervals and a real number (x_interval, y_interval, x_measure) 
    double x_measure;

    /**
     * @brief Default Constructor.
     */
    StripeMeasure() {}

    /**
     * @brief Constructor to initialize stripe for contour function using two Intervals x-interval, y-interval and a double variable x_measure
     * @param[in] x_interval x_interval of the stripe
     * @param[in] y_interval y_interval of the stripe
     * @param[in] x_measure real value of length of x_interval occupied by rectangles in a stripe
     */
    StripeMeasure(Interval x_interval, Interval y_interval, double x_measure)
    {
        this->x_interval = x_interval;
        this->y_interval = y_interval;
        this->x_measure = x_measure;
    }

    /**
     * @brief Compares two StripeMeasure objects.
     * @return @a true if stripes are same, else @a false
     */
    bool operator==(const StripeMeasure &S) const
    {
        return this->x_interval == S.x_interval && this->y_interval == S.y_interval && this->x_measure == S.x_measure;
    }

    /**
     * @brief Compares two StripeMeasure objects.
     * @return @a true if stripes are different, else @a false
     */
    bool operator!=(const StripeMeasure &S) const
    {
        return this->x_interval != S.x_interval || this->y_interval != S.y_interval || this->x_measure != S.x_measure;
    }

    /**
     * @brief Compares two StripeMeasure objects.
        * Priority for ordering - @a x_interval > @a y_interval > @a x_measure
     * @return @a true if first StripeMeasure object < second StripeMeasure object, else @a false
     */
    bool operator<(const StripeMeasure &S) const
    {
        return this->x_interval != S.x_interval   ? this->x_interval < S.x_interval
               : this->y_interval != S.y_interval ? this->y_interval < S.y_interval
                                                  : this->x_measure < S.x_measure;
    }
};

#endif