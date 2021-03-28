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
#include <sstream>
#include "methods_contour.hpp"
#include "methods_measure.hpp"

/**
 * @brief Driver function to read the file, compute measure and contour and write back to another file.
 * @param[in] argc Number of arguments
 * @param[in] argv Name of the file to open
 * @return (int) 0
 */
int main(int argc, char *argv[])
{
    set<Rectangle> Rect, Rect_F;
    set<StripeMeasure> SM;
    set<StripeContour> SC, SC_F;
    set<Edge> H, H_F;
    Rect.clear();
    Rect_F.clear();
    SM.clear();
    SC.clear();
    SC_F.clear();
    H.clear();
    H_F.clear();

    double area = 0, clength = 0;

    fstream testcase;
    string fname = "testcases/" + string(argv[1]);
    testcase.open(fname, ios::in);
    string inp;
    coord x_left, y_bottom, x_right, y_top;
    while (getline(testcase, inp))
    {
        stringstream ss(inp);
        ss >> x_left >> y_bottom >> x_right >> y_top;

        if (x_left > x_right)
        {
            swap(x_left, x_right);
        }
        if (y_bottom > y_top)
        {
            swap(y_bottom, y_top);
        }

        Rect.insert(Rectangle(x_left, x_right, y_top, y_bottom));
        H.insert(Edge(y_top, x_right, x_left, EdgeType::top_edge));
        H.insert(Edge(y_bottom, x_right, x_left, EdgeType::bottom_edge));

        Rect_F.insert(Rectangle(y_bottom, y_top, x_right, x_left));
        H_F.insert(Edge(x_right, y_top, y_bottom, EdgeType::top_edge));
        H_F.insert(Edge(x_left, y_top, y_bottom, EdgeType::bottom_edge));
    }

    RECTANGLE_DAC(Rect, SM);
    RECTANGLE_DAC(Rect, SC);
    area = measure(SM);
    set<LineSegment> L = contour(H, SC);

    RECTANGLE_DAC(Rect_F, SC_F);
    set<LineSegment> L_M = contour(H_F, SC_F);

    ofstream output;
    output.open(fname + "_out.txt");
    for (auto i : L)
    {
        clength += i.interval.upper - i.interval.lower;
        cout << i.interval.lower << " " << i.cord << " " << i.interval.upper << " " << i.cord << "\n";
        output << i.interval.lower << " " << i.cord << " " << i.interval.upper << " " << i.cord << "\n";
    }
    for (auto i : L_M)
    {
        clength += i.interval.upper - i.interval.lower;
        cout << i.cord << " " << i.interval.lower << " " << i.cord << " " << i.interval.upper << "\n";
        output << i.cord << " " << i.interval.lower << " " << i.cord << " " << i.interval.upper << "\n";
    }
    cout << "\nMeasure = " << area << " Contour Length = " << clength << endl;
    output << "\nMeasure = " << area << " Contour Length = " << clength << endl;

    output.close();
    return 0;
}