/**
 * @file ctree.hpp
 * Header file for including Ctree class
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#ifndef CTREE_HPP
#define CTREE_HPP

#include "coord.hpp"

/// Enumeration lru{left, right, undef} is used in Ctree
enum lru
{
    left,
    right,
    undef
};

/// Ctree object is used in StripeContour
class Ctree
{
public:
    /// coord stored in Ctree
    coord x;
    /// Denotes whether coord x is left(starting) or right(ending)
    lru side;
    /// Pointer to left child
    Ctree *lson;
    /// Pointer to right child
    Ctree *rson;

    /**
     * @brief Default Constructor.
     */
    Ctree() {}

    /**
     * @brief Constructor accepting coord and lru.
     * @param[in] x coord x
     * @param[in] side lru side
     */
    Ctree(coord x, lru side)
    {
        this->x = x;
        this->side = side;
        this->lson = nullptr;
        this->rson = nullptr;
    }

    /**
     * @brief Constructor accepting four parameters.
     * @param[in] x coord x
     * @param[in] side lru side
     * @param[in] lson pointer to left child
     * @param[in] rson pointer to right child
     */
    Ctree(coord x, lru side, Ctree *lson, Ctree *rson)
    {
        this->x = x;
        this->side = side;
        this->lson = lson;
        this->rson = rson;
    }

    /**
     * @brief Function to compare two Ctree pointers.
        * Checks if the pointers point to same Ctree.
        * If not, it compares the contents of the two Ctrees.
     * @param[in] first pointer to first Ctree
     * @param[in] second pointer to second Ctree
     * @return @a true if any condition is satisfied, else @a false
     * @see Ctree::ptrneq()
     * @see Ctree::operator==()
     */
    bool ptreq(const Ctree *first, const Ctree *second) const
    {
        return first == second                         ? true
               : first != nullptr && second != nullptr ? *first == *second
                                                       : false;
    }

    /**
     * @brief Negation of Ctree::ptreq function.
     * @param[in] first pointer to first Ctree
     * @param[in] second pointer to second Ctree
     * @return @a true if Ctrees are different, else @a false
     * @see Ctree::ptreq()
     * @see Ctree::operator!=()
     */
    bool ptrneq(const Ctree *first, const Ctree *second) const
    {
        return first == second                         ? false
               : first != nullptr && second != nullptr ? *first != *second
                                                       : true;
    }

    /**
     * @brief Function to compare two Ctree objects, including their children.
     * @return @a true if Ctrees are same, else @a false
     * @see Ctree::ptreq()
     * @see Ctree::operator!=()
     */
    bool operator==(const Ctree &C) const
    {
        return this->x == C.x && this->side == C.side && ptreq(this->lson, C.lson) && ptreq(this->rson, C.rson);
    }

    /**
     * @brief Function to compare two Ctree objects, including their children.
     * @return @a true if Ctrees are different, else @a false
     * @see Ctree::ptrneq()
     * @see Ctree::operator==()
     */
    bool operator!=(const Ctree &C) const
    {
        return this->x != C.x || this->side != C.side || ptrneq(this->lson, C.lson) || ptrneq(this->rson, C.rson);
    }

    /**
     * @brief Function to order the Ctree objects.
        * Priority for ordering - @a x > @a side > @a lson > @a rson
     * @return @a true if first ctree < second ctree, else @a false
     */
    bool operator<(const Ctree &C) const
    {
        return this->x != C.x         ? this->x < C.x
               : this->side != C.side ? this->side < C.side
               : this->lson != C.lson ? this->lson < C.lson
                                      : this->rson < C.rson;
    }
};

#endif