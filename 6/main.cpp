#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// https://www.geeksforgeeks.org/determine-string-unique-characters/
bool uniqueCharacters(string str)
{

    // Assuming string can have characters
    // a-z, this has 32 bits set to 0
    int checker = 0;

    for (int i = 0; i < str.length(); i++)
    {

        int bitAtIndex = str[i] - 'a';

        // if that bit is already set in
        // checker, return false
        if ((checker & (1 << bitAtIndex)) > 0)
        {
            return false;
        }

        // otherwise update and continue by
        // setting that bit in the checker
        checker = checker | (1 << bitAtIndex);
    }

    // no duplicates encountered, return true
    return true;
}

int main()
{
    fstream stream;

    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";
        // part one: 4
        // part two: 14
        int marker_length = 14;

        while (getline(stream, line))
        {
            bool isMarker = false;
            int marker_position = 0;

            while (!isMarker)
            {
                ++marker_position;
                string marker = line.substr(marker_position, marker_length);
                isMarker = uniqueCharacters(marker);
            }
            cout << marker_position + marker_length << endl;
        }

        stream.close(); // close the file object.
    }
}