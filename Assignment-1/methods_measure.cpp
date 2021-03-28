#include "methods_measure.hpp"

set<Interval> partition(set<coord> Y)
{
    set<Interval> result;
    result.clear();
    for (auto it = Y.begin(); next(it) != Y.end(); it++)
    {
        result.insert(Interval(*it, *next(it)));
    }
    return result;
}

void RECTANGLE_DAC(set<Rectangle> Rect, set<StripeMeasure> &S)
{
    set<Edge> VRX;
    VRX.clear();
    for (auto i : Rect)
    {
        VRX.insert(Edge(i.x_left, i.y_top, i.y_bottom, EdgeType::left_edge));
        VRX.insert(Edge(i.x_right, i.y_top, i.y_bottom, EdgeType::right_edge));
    }
    set<Interval> LEFT, RIGHT;
    set<coord> POINTS;
    LEFT.clear();
    RIGHT.clear();
    POINTS.clear();
    STRIPES(VRX, Interval(-INFINITY, INFINITY), LEFT, RIGHT, POINTS, S);
}

void STRIPES(set<Edge> V, Interval x_ext, set<Interval> &L, set<Interval> &R, set<coord> &P, set<StripeMeasure> &S)
{
    if (V.size() == 1)
    {
        Edge v = *(V.cbegin());
        if (v.side == EdgeType::left_edge)
        {
            L.clear();
            L.insert(v.interval);
            R.clear();
        }
        else
        {
            L.clear();
            R.clear();
            R.insert(v.interval);
        }
        P.clear();
        P.insert(-INFINITY);
        P.insert(v.interval.lower);
        P.insert(v.interval.upper);
        P.insert(INFINITY);

        S.clear();
        for (auto i : partition(P))
        {
            S.insert(StripeMeasure(x_ext, i, 0)); //A
        }

        set<StripeMeasure> S1;
        S1.clear();
        for (auto s : S)
        {
            if (s.y_interval == v.interval)
            {
                if (v.side == EdgeType::left_edge)
                {
                    s.x_measure = x_ext.upper - v.cord; //B
                }
                else
                {
                    s.x_measure = v.cord - x_ext.lower; //C
                }
            }
            S1.insert(s);
        }
        S = S1;
    }

    else
    {
        set<Edge> V1, V2;
        set<Interval> L1, L2, R1, R2, LR;
        set<coord> P1, P2;
        set<StripeMeasure> S1, S2;
        V1.clear();
        V2.clear();
        L1.clear();
        L2.clear();
        R1.clear();
        R2.clear();
        LR.clear();
        P1.clear();
        P2.clear();
        S1.clear();
        S2.clear();

        // Divide
        auto it = next(V.begin(), V.size() / 2);
        coord xm = it->cord;
        copy(V.cbegin(), it, inserter(V1, V1.end()));
        copy(it, V.cend(), inserter(V2, V2.end()));

        // Conquer
        STRIPES(V1, Interval(x_ext.lower, xm), L1, R1, P1, S1);
        STRIPES(V2, Interval(xm, x_ext.upper), L2, R2, P2, S2);

        // Merge
        set<Interval> tmp1, tmp2;
        tmp1.clear();
        tmp2.clear();

        set_intersection(L1.cbegin(), L1.cend(), R2.cbegin(), R2.cend(), inserter(LR, LR.end()));

        L.clear();
        set_difference(L1.cbegin(), L1.cend(), LR.cbegin(), LR.cend(), inserter(tmp1, tmp1.end()));
        set_union(tmp1.cbegin(), tmp1.cend(), L2.cbegin(), L2.cend(), inserter(L, L.end()));

        R.clear();
        set_difference(R2.cbegin(), R2.cend(), LR.cbegin(), LR.cend(), inserter(tmp2, tmp2.end()));
        set_union(R1.cbegin(), R1.cend(), tmp2.cbegin(), tmp2.cend(), inserter(R, R.end()));

        P.clear();
        set_union(P1.cbegin(), P1.cend(), P2.cbegin(), P2.cend(), inserter(P, P.end()));

        set<StripeMeasure> Sleft = copy(S1, P, Interval(x_ext.lower, xm));
        set<StripeMeasure> SRight = copy(S2, P, Interval(xm, x_ext.upper));

        blacken(Sleft, tmp2);
        blacken(SRight, tmp1);

        S = concat(Sleft, SRight, P, x_ext);
    }
}

set<StripeMeasure> copy(set<StripeMeasure> S, set<coord> P, Interval x_int)
{
    set<StripeMeasure> S1;
    S1.clear();
    for (auto i : partition(P))
    {
        S1.insert(StripeMeasure(x_int, i, 0));
    }
    set<StripeMeasure> newS1;
    newS1.clear();
    for (auto s1 : S1)
    {
        for (auto s : S)
        {
            if (s.y_interval.isSupersetOf(s1.y_interval))
            {
                s1.x_measure = s.x_measure; //D
                break;
            }
        }
        newS1.insert(s1);
    }
    return newS1;
}

void blacken(set<StripeMeasure> &S, set<Interval> J)
{
    set<StripeMeasure> S1;
    S1.clear();
    for (auto s : S)
    {
        for (auto i : J)
        {
            if (i.isSupersetOf(s.y_interval))
            {
                s.x_measure = s.x_interval.upper - s.x_interval.lower; //E
                break;
            }
        }
        S1.insert(s);
    }
    S = S1;
}

set<StripeMeasure> concat(set<StripeMeasure> S1, set<StripeMeasure> S2, set<coord> P, Interval x_int)
{
    set<StripeMeasure> S, S_new;
    S.clear();
    S_new.clear();
    for (auto i : partition(P))
    {
        S.insert(StripeMeasure(x_int, i, 0));
    }
    for (auto s : S)
    {
        StripeMeasure s1, s2;
        for (auto i : S1)
        {
            if (i.y_interval == s.y_interval)
            {
                s1 = i;
                break;
            }
        }
        for (auto i : S2)
        {
            if (i.y_interval == s.y_interval)
            {
                s2 = i;
                break;
            }
        }
        s.x_measure = s1.x_measure + s2.x_measure; //F
        S_new.insert(s);
    }
    return S_new;
}

double measure(set<StripeMeasure> S)
{
    double out = 0;
    for (auto s : S)
    {
        if (s.y_interval.lower == -INFINITY || s.y_interval.upper == INFINITY)
        {
            continue;
        }
        out += s.x_measure * (s.y_interval.upper - s.y_interval.lower);
    }
    return out;
}