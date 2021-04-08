#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include "functions.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    string f = argv[1];
    string filename;
    filename = "autotestcase/" + f;
    ifstream filep(filename);
    ofstream fp("cost_err.txt");
    vector<Point> input;
    double cost;
    while (!filep.eof())
    {
        double x, y;
        filep >> x;
        filep >> y;
        input.push_back(Point(x, y));
    }

    sort(input.begin(), input.end(), [](const Point &a, const Point &b) -> bool {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    input.insert(input.begin(), Point(-INFINITY, -INFINITY));
    int n = input.size() - 1;

    //cout << n << endl;
    for(cost = -10 ; cost < 101 ; cost++){
        vector<double> M(n + 1, 0);
        vector<vector<double>> Err;
        Segmented_Least_Square(input, cost, M, Err);

        vector<vector<Point>> result;
        Find_Segment(n, input, M, cost, Err, result);

        int c = 1;
        reverse(result.begin(), result.end());
        double tot_error = 0;
        for (auto i : result)
        {
            Line L = Line(i);
            for (auto j : i)
            {
                tot_error += L.err(j);
            }
        }
        fp << cost << " " << tot_error << " " << result.size() << endl;
    }
}