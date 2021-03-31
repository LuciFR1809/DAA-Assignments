#include<iostream>
#include<fstream>
#include <bits/stdc++.h>

#include "functions.hpp"

using namespace std;

int main(){

    string filename;
    cout << "Please enter the filename " ;
    cin >> filename;
    filename = "testcases/" +filename;
    ifstream filep (filename);
    vector<Point> input;

    double cost;
    cout << "Please enter the cost " ;
    cin >> cost;

//error : taking last line twice
    while(!filep.eof())
    {
        double x, y;
        filep >> x;
        filep >> y;
        input.push_back(Point(x,y));
    }

    sort(input.begin(), input.end(), [](const Point & a, const Point & b) -> bool
    { 
        return a.x < b.x || (a.x == b.x && a.y < b.y); 
    });

    input.insert(input.begin(),Point(-INFINITY,-INFINITY));
    int n = input.size()-1;

    cout << n << endl;

    vector<double> M(n+1,0);
    vector<vector<double>> Err;
    Segmented_Least_Square(input, cost, M, Err);


    vector<vector<Point>> result;
    Find_Segment(n, input, M, cost, Err, result);


    int c = 1;
    reverse(result.begin(), result.end());
    ofstream ofp(filename+"_out.txt");
    for(auto i : result){
        Line L = Line(i);
        ofp << "Partition " << c++  << " : Line [ y = " << L.a << "*x + " << L.b << " ]"<< endl;
        for(auto j : i){
            ofp << j.x << " " << j.y << endl;
        }
    }
    ofp.close();
}

// doubt : what to output and how to show final result, how correct is implementation
