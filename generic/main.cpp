#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../useful_functions.h"

int main()
{
    std::fstream stream;
    stream.open("input.txt", std::ios::in);

    if (stream.is_open())
    {
        std::string line = "";

        while (getline(stream, line))
        {
        }

        stream.close();
    }

    return 0;
};