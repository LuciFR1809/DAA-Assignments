#include "methods_contour.hpp"

void RECTANGLE_DAC(set<Rectangle> Rect, set<StripeContour> &S)
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

void STRIPES(set<Edge> V, Interval x_ext, set<Interval> &L, set<Interval> &R, set<coord> &P, set<StripeContour> &S)
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
            S.insert(StripeContour(x_ext, i, nullptr)); //A
        }

        set<StripeContour> S1;
        S1.clear();
        for (auto s : S)
        {
            if (s.y_interval == v.interval)
            {
                if (v.side == EdgeType::left_edge)
                {
                    s.tree = new Ctree(v.cord, lru::left); //B
                }
                else
                {
                    s.tree = new Ctree(v.cord, lru::right); //C
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
        set<StripeContour> S1, S2;
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

        set<StripeContour> Sleft = copy(S1, P, Interval(x_ext.lower, xm));
        set<StripeContour> SRight = copy(S2, P, Interval(xm, x_ext.upper));

        blacken(Sleft, tmp2);
        blacken(SRight, tmp1);

        S = concat(Sleft, SRight, P, x_ext);
    }
}

set<StripeContour> copy(set<StripeContour> S, set<coord> P, Interval x_int)
{
    set<StripeContour> S1;
    S1.clear();
    for (auto i : partition(P))
    {
        S1.insert(StripeContour(x_int, i, nullptr));
    }
    set<StripeContour> newS1;
    newS1.clear();
    for (auto s1 : S1)
    {
        for (auto s : S)
        {
            if (s.y_interval.isSupersetOf(s1.y_interval))
            {
                s1.tree = s.tree; //D
                break;
            }
        }
        newS1.insert(s1);
    }
    return newS1;
}

void blacken(set<StripeContour> &S, set<Interval> J)
{
    set<StripeContour> S1;
    S1.clear();
    for (auto s : S)
    {
        for (auto i : J)
        {
            if (i.isSupersetOf(s.y_interval))
            {
                s.tree = nullptr; //E
                break;
            }
        }
        S1.insert(s);
    }
    S = S1;
}

set<StripeContour> concat(set<StripeContour> S1, set<StripeContour> S2, set<coord> P, Interval x_int)
{
    set<StripeContour> S, S_new;
    S.clear();
    S_new.clear();
    for (auto i : partition(P))
    {
        S.insert(StripeContour(x_int, i, nullptr));
    }
    for (auto s : S)
    {
        StripeContour s1, s2;
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
        s.tree = //F
            s1.tree != nullptr && s2.tree != nullptr  ? new Ctree(s1.x_interval.upper, lru::undef, s1.tree, s2.tree)
            : s1.tree != nullptr &&s2.tree == nullptr ? s1.tree
            : s1.tree == nullptr &&s2.tree != nullptr ? s2.tree
                                                      : nullptr;
        S_new.insert(s);
    }
    return S_new;
}

set<LineSegment> postProcess(set<LineSegment> L)
{
    set<LineSegment> result;
    map<coord, vector<Ctree>> m;
    result.clear();
    m.clear();
    for (auto i : L)
    {
        coord c = i.cord;
        auto it = m.find(c);
        if (it == m.end())
        {
            vector<Ctree> v;
            v.clear();
            v.push_back(Ctree(i.interval.lower, lru::left));
            v.push_back(Ctree(i.interval.upper, lru::right));
            m.insert(pair<coord, vector<Ctree>>(c, v));
        }
        else
        {
            it->second.push_back(Ctree(i.interval.lower, lru::left));
            it->second.push_back(Ctree(i.interval.upper, lru::right));
        }
    }
    for (auto i : m)
    {
        int count = 0;
        Ctree start;
        vector<Ctree> V = i.second;
        sort(V.begin(), V.end());
        for (auto j : V)
        {
            if (count == 0)
            {
                start = j;
                count++;
            }
            else if (j.side == lru::left)
            {
                count++;
            }
            else
            {
                count--;
            }
            if (count == 0)
            {
                result.insert(LineSegment(Interval(start.x, j.x), i.first));
            }
        }
    }
    return result;
}

void traverseCtree(Ctree *C, vector<coord> &start, vector<coord> &end)
{
    if (C == nullptr)
    {
        return;
    }
    if (C->side == lru::left)
    {
        start.push_back(C->x);
        return;
    }
    if (C->side == lru::right)
    {
        end.push_back(C->x);
        return;
    }
    traverseCtree(C->lson, start, end);
    traverseCtree(C->rson, start, end);
}

set<Interval> getIntervals(Ctree *C)
{
    set<Interval> result;
    vector<coord> start, end;
    result.clear();
    start.clear();
    end.clear();
    traverseCtree(C, start, end);
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    for (int i = 0; i < min(start.size(), end.size()); i++)
    {
        result.insert(Interval(start[i], end[i]));
    }
    return result;
}

set<LineSegment> contour_pieces(Edge h, set<StripeContour> S)
{
    StripeContour s;
    if (h.side == EdgeType::bottom_edge)
    {
        for (auto i : S)
        {
            if (i.y_interval.upper == h.cord)
            {
                s = i;
                break;
            }
        }
    }
    else
    {
        for (auto i : S)
        {
            if (i.y_interval.lower == h.cord)
            {
                s = i;
                break;
            }
        }
    }
    set<Interval> x_union = getIntervals(s.tree);
    set<Interval> J = h.interval.difference(x_union);
    set<LineSegment> result;
    result.clear();
    for (auto i : J)
    {
        result.insert(LineSegment(i, h.cord));
    }
    return result;
}

set<LineSegment> contour(set<Edge> H, set<StripeContour> S)
{
    set<LineSegment> result;
    result.clear();
    for (auto h : H)
    {
        set<LineSegment> res = contour_pieces(h, S);
        set<LineSegment> tmp;
        tmp.clear();
        set_union(result.cbegin(), result.cend(), res.cbegin(), res.cend(), inserter(tmp, tmp.end()));
        result = tmp;
    }
    return postProcess(result);
}