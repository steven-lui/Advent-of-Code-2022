#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
    fstream stream;
    list<int> calories;

    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";
        int count = 0;

        while (getline(stream, line))
        {
            if (line == "") // new elf
            {
                calories.push_back(count);
                count = 0;
            }
            // check for final line
            else
                count += stoi(line);
        }

        // final number
        calories.push_back(count);

        // sort by size
        calories.sort();

        // PART 1: MAX CALORIES
        cout << calories.back() << endl;

        // PART 2: SUM OF TOP THREE
        int topThree;
        for (size_t i = 0; i < 3; i++)
        {
            topThree += calories.back();
            calories.pop_back();
        }
        cout << topThree << endl;

        stream.close(); // close the file object.
    }
}