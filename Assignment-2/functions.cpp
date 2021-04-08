#include <vector>
#include <iostream>
#include "point.hpp"
#include "line.hpp"
#include "functions.hpp"
#define MAX 10000000

using namespace std;

vector<Point> slice(int i, int j, vector<Point> P)
{
    vector<Point> result(j - i + 1);
    auto start = P.begin() + i;
    auto end = P.begin() + j + 1;
    copy(start, end, result.begin());
    return result;
}

double cal_err(vector<Point> P)
{
    if(P.size() <= 1)
    {
        return 0;
    }
    Line L = Line(P);

    double error = 0;
    for (auto i : P)
        error += L.err(i);

    return error;
}

//indices : 0 1 2 3 4 5 6  M -> 0 : n-1    new M -> 0 : n
//M[0]                               M[0] mthmg
//M[1] 0,1    2 elements taken                             M[1] -> 0,1           1 element taken
//M[2] 0,1,2  3 elements taken                             M[2] -> 0,1,2         2 elements taken

void OPT(int j, double cost, vector<double> &M, vector<vector<double>> Err)
{
    double min = MAX;

    for (int i = 1; i <= j; i++)
    {
        double s = Err[i][j - i] + cost + M[i - 1];

        if (s < min)
            min = s;
    }

    M[j] = min;
    return;
}

void Segmented_Least_Square(vector<Point> P, double cost, vector<double> &M, vector<vector<double>> &Err)
{
    int n = P.size() - 1;
    Err.push_back(vector<double>(n, 0));

    for (int i = 1; i <= n; i++)
    {
        Err.push_back(vector<double>(n - i + 1, 0)); //if allowing one point then make INFINITY 0

        for (int j = i + 1; j <= n; j++)
            Err[i][j - i] = cal_err(slice(i, j, P));
    }
    // i = 0 j = 1   0,1       - Err[0][0]
    // i = 0 j = 2  0,1,2      - Err[0][1]
    // i = 3 j = 7  3,4,5,6,7  - Err[i][j-i-1]

    for (int j = 1; j <= n; j++)
    {
        OPT(j, cost, M, Err);
    }
}

void Find_Segment(int j, vector<Point> P, vector<double> M, double cost, vector<vector<double>> Err, vector<vector<Point>> &result)
{
    if (j <= 0)
        return;

    else
    {
        int min_index;
        double min = MAX;

        for (int i = 1; i <= j; i++)
        {
            double s = M[i - 1] + cost + Err[i][j - i];

            if (s < min)
            {
                min = s;
                min_index = i;
            }
        }

        result.push_back(slice(min_index, j, P));
        Find_Segment(min_index - 1, P, M, cost, Err, result);
    }
}