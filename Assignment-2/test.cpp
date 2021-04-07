#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include "functions.hpp"

int main(int argc, char *argv[]) // Don't forget first integral argument 'argc'
{
  string f = argv[1]; // Name of the current exec program
  double cost = strtod(argv[2], NULL);
  cout << f << " " << cost;
  return 0;
}