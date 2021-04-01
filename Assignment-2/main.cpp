#include<iostream>
#include<fstream>
#include <bits/stdc++.h>
#include<string>
#include "functions.hpp"

using namespace std;

int main(int argc, char *argv[]){
string f = argv[1];
    string filename;
    filename = "testcases/" +f;
    ifstream filep (filename);
    vector<Point> input;
    double cost=strtod(argv[2],NULL);
//cout<<f<<" "<<cost;
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

    //cout << n << endl;

    vector<double> M(n+1,0);
    vector<vector<double>> Err;
    Segmented_Least_Square(input, cost, M, Err);


    vector<vector<Point>> result;
    Find_Segment(n, input, M, cost, Err, result);


    int c = 1;
    reverse(result.begin(), result.end());
    ofstream ofp(filename+"_out.txt");
    ofstream ofp2(filename+"_line.txt");
    double tot_error=0;
    for(auto i : result){
        Line L = Line(i);
        ofp << "Partition " << c++  << " : Line [ y = " << L.a << "*x + " << L.b << " ]"<< endl;
        for(auto j : i){
            tot_error+=L.err(j);
            ofp << j.x << " " << j.y<<endl;
        }
        ofp2<<tot_error<<" "<<L.a<<" "<<L.b<<" "<<i.begin()->x<<" "<<(i.end()-1)->x<<endl;
    }
    ofp.close();
    ofp2.close();
}

// doubt : what to output and how to show final result, how correct is implementation
