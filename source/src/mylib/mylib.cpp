
#include <iostream>
#include <fstream>
#include "mylib.hpp"

int insaneMath(int val)
{
    std::cout << 42 << std::endl;
    std::ofstream myfile;
    myfile.open ("example.txt");
    myfile << "Writing this to a file.\n";
    myfile.close();
    return 42;
}