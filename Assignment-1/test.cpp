/**
 * @file test.cpp
 * Main file for testing the runtime of program. Contains the driver code for reading and writing to file.
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "methods_contour.hpp"
#include "methods_measure.hpp"

using namespace std::chrono;

/**
 * @brief Driver function to read the file, compute measure and contour and write back to another file.
 * @return (int) 0
 */
int main()
{
    ofstream output;
    output.open("autotestcase/time.txt");

    for (int i = 1; i <= 500; i++)
    {
        cout << i << endl;
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

        fstream testcase;
        string fname = "autotestcase/" + to_string(i) + ".txt";
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

        auto start = high_resolution_clock::now();

        RECTANGLE_DAC(Rect, SM);
        RECTANGLE_DAC(Rect, SC);
        measure(SM);
        contour(H, SC);

        RECTANGLE_DAC(Rect_F, SC_F);
        contour(H_F, SC_F);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        output << (duration.count() / 1000) << endl;
    }

    output.close();
    return 0;
}