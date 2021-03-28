/**
 * @file interval.hpp
 * Header file for including Interval class
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "coord.hpp"

/// Interval object is used in various phases of the algorithm
class Interval
{
public:
    /// lower endpoint of interval
    coord lower;
    /// higher endpoint of interval
    coord upper;

    /**
     * @brief Default constructor.
     */
    Interval() {}

    /**
     * @brief Constructor accepting lower and upper endpoints.
     * @param[in] lower lower endpoint
     * @param[in] upper upper endpoint
     */
    Interval(coord lower, coord upper)
    {
        this->lower = lower;
        this->upper = upper;
    }

    /**
     * @brief Compares two Interval objects.
     * @return @a true if intervals are same, else @a false
     */
    bool operator==(const Interval &I) const
    {
        return this->lower == I.lower && this->upper == I.upper;
    }

    /**
     * @brief Compares two Interval objects.
     * @return @a true if intervals are different, else @a false
     */
    bool operator!=(const Interval &I) const
    {
        return this->lower != I.lower || this->upper != I.upper;
    }

    /**
     * @brief Function to order the Interval objects.
        * Priority for ordering - @a lower > @a upper
     * @return @a true if first interval < second interval, else @a false
     */
    bool operator<(const Interval &I) const
    {
        return this->lower != I.lower ? this->lower < I.lower
                                      : this->upper < I.upper;
    }

    /**
     * @brief Function to check whether @a this Interval is superset of Interval @a I .
     * @param[in] I parameter Interval
     * @return @a true if @a this is superset of @a I , else @a false
     * @note It checks for superset and not proper superset
     */
    bool isSupersetOf(const Interval &I) const
    {
        return this->lower <= I.lower && this->upper >= I.upper;
    }

    /**
     * @brief Function to find intersection between @a this Interval and set of Interval @a J .
     * @param[in] J set of Interval to find intersection with
     * @return set of Interval after calculating intersection
     */
    std::set<Interval> intersection(std::set<Interval> J)
    {
        std::set<Interval> result;
        result.clear();
        for (auto i : J)
        {
            if (this->isSupersetOf(i))
            {
                result.insert(i);
            }
            else if (i.isSupersetOf(*this))
            {
                result.insert(*this);
            }
            else if (i.lower < this->lower && this->lower < i.upper && i.upper < this->upper)
            {
                result.insert(Interval(this->lower, i.upper));
            }
            else if (this->lower < i.lower && i.lower < this->upper && this->upper < i.upper)
            {
                result.insert(Interval(i.lower, this->upper));
            }
        }
        return result;
    }

    /**
     * @brief Function to find difference between @a this Interval and set of Interval @a J .
     * @param[in] J set of Interval to find difference with
     * @return set of Interval after calculating difference
     */
    std::set<Interval> difference(std::set<Interval> J)
    {
        std::set<Interval> result;
        result.clear();
        Interval remaining = *this;
        J = remaining.intersection(J);
        while (J.size() > 0)
        {
            Interval i = *(J.begin());
            if (i.lower > remaining.lower)
            {
                result.insert(Interval(remaining.lower, i.lower));
            }
            remaining.lower = i.upper;
            if (remaining.lower >= remaining.upper)
            {
                break;
            }
            J = remaining.intersection(J);
        }
        if(remaining.lower < remaining.upper)
        {
            result.insert(Interval(remaining.lower, remaining.upper));
        }
        return result;
    }
};

#endif