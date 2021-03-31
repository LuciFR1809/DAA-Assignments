#include<vector>
#include<iostream>
#include "point.hpp"
#include "line.hpp"
#include "functions.hpp"
#define MAX 10000000

using namespace std;

vector<Point> slice(int i, int j, vector<Point> P)
{
    vector<Point>result(j-i+1);
    auto start = P.begin()+i;
    auto end = P.begin()+j+1;
    copy(start, end, result.begin());
    return result;

}

double cal_err(vector<Point> P)
{
    Line L = Line(P);

    double error = 0;
    for(auto i : P)
        error += L.err(i);

    return error;

}

void OPT(int j, double cost, vector<double>& M,vector<vector<double>> Err)
{  
    double min = MAX;

    for(int i = 0; i < j; i++)
    {
        double s = Err[i][j]+cost+M[i];

        if(s < min)
            min = s;
    }  

    M[j] = min;
    return;
}

void Segmented_Least_Square(vector<Point> P, double cost, vector<double>& M, vector<vector<double>>& Err)
{
    int n = P.size();

    for (int i = 0; i < n; i++)
    {
        Err.push_back(vector<double> (n-i-1,0));

        for(int j = i+1; j < n; j++)
            Err[i][j-i-1] = cal_err(slice(i,j,P));
    }

    for(int j = 1; j < n; j++)
    {
        OPT(j, cost, M, Err);
    }

}

void Find_Segment(int j, vector<Point> P, vector<double> M, double cost, vector<vector<double>> Err, vector<vector<Point>>& result)
{
    if(j < 0)
        return;
    
    else
    {
        int min_index;
        double min = MAX;

        for(int i = 0; i < j; i++)
        {
            double s = M[i-1]+cost+Err[i][j-i-1];
        
            if(s < min){
                min = s;
                min_index = i;
            }
        }

        result.push_back(slice(min_index,j,P));
        Find_Segment(min_index-1, P, M, cost, Err, result);
    }

}