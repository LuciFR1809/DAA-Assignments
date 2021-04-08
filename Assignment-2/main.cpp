/**
 * @file main.cpp
 * Main file of the program. Contains the driver code for reading and writing to file.
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include "functions.hpp"

using namespace std;

/**
 * @brief Driver function to read the file, compute partitions and write back to another file.
 * @param[in] argc Number of arguments
 * @param[in] argv Name of the file to open
 * @return (int) 0
 */
int main(int argc, char *argv[])
{
    string f = argv[1];
    string filename;
    filename = "autotestcase/" + f;
    ifstream filep(filename);
    vector<Point> input;
    double cost = strtod(argv[2], NULL);
    string inp;
    while (getline(filep, inp))
    {
        stringstream ss(inp);
        double x, y;
        ss >> x >> y;
        input.push_back(Point(x, y));
    }

    sort(input.begin(), input.end(), [](const Point &a, const Point &b) -> bool {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    input.insert(input.begin(), Point(-INFINITY, -INFINITY));
    int n = input.size() - 1;

    vector<double> M(n + 1, 0);
    vector<vector<double>> Err;
    Segmented_Least_Square(input, cost, M, Err);

    vector<vector<Point>> result;
    Find_Segment(n, input, M, cost, Err, result);

    int c = 1;
    reverse(result.begin(), result.end());
    ofstream ofp(filename + "_out.txt");
    ofstream ofp2(filename + "_line.txt");
    double tot_error = 0;
    for (auto i : result)
    {
        Line L = Line(i);
        ofp << "Partition " << c++ << " : Line [ y = " << L.a << "*x + " << L.b << " ]" << endl;
        for (auto j : i)
        {
            double e = L.err(j);
            if(isnan(e))
            {
                e = 0;
            }
            tot_error += e;
            ofp << j.x << " " << j.y << endl;
        }
        ofp2 << tot_error << " " << L.a << " " << L.b << " " << i.begin()->x << " " << (i.end() - 1)->x << endl;
    }
    ofp.close();
    ofp2.close();
}
