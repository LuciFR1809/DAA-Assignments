/**
 * @file testcasegenerator.cpp
 * Testcase generating file for the program.
 * 
 * @authors Kumar Pranjal 2018A7PS0163H
 * @authors Ashna Swaika 2018A7PS0027H
 * @authors Abhishek Bapna 2018A7PS0184H
 * @authors Ashish Verma 2018A7PS0009H
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

/**
 * @brief Driver function to write to the file.
 * @return (int) 0
 */
int main()
{
    srand(time(0));
    int limit = 101;
    for (int i = 1; i <= 500; i++)
    {
        ofstream output;
        output.open("autotestcase/" + to_string(i) + ".txt");
        for (int j = 1; j <= i; j++)
        {
            int a, b, c, d;
            a = rand() % limit;
            b = rand() % limit;
            c = rand() % limit;
            d = rand() % limit;
            if (a == c)
            {
                c = (c + 1) % limit;
            }
            if (b == d)
            {
                d = (d + 1) % limit;
            }
            output << a << " " << b << " " << c << " " << d << endl;
        }
        output.close();
    }
    return 0;
}