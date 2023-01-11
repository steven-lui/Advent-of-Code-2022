#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

int total(list<int> l)
{
    int s = 0;
    for (list<int>::iterator i = l.begin(); i != l.end(); ++i)
        s += *i;
    return s;
}

int letter_to_number(char c)
{
    return int(c) - (int(c) > 96 ? 96 : 38);
}

int total_for_line(string line)
{
    // each compartment
    string one = line.substr(0, line.length() / 2);
    string two = line.substr(line.length() / 2);
    list<int> common;

    // check if characters in string one appear in string two
    for (size_t i = 0; i < one.length(); i++)
    {
        for (size_t j = 0; j < two.length(); j++)
        {
            // found a duplicate
            if (one[i] == two[j])
            {
                bool found = (std::find(common.begin(), common.end(), letter_to_number(one[i])) != common.end());
                // if not already in list
                if (!found)
                {
                    common.push_back(letter_to_number(one[i]));
                }
            }
        }
    }

    return total(common);
}

char get_common_letter(string one, string two, string three)
{
    list<char> temp;
    char out;

    // check if characters in string one appear in string two
    for (size_t i = 0; i < one.length(); i++)
    {
        for (size_t j = 0; j < two.length(); j++)
        {
            // found a duplicate
            if (one[i] == two[j])
            {
                temp.push_back(one[i]);
            }
        }
    }

    // check if characters in temp appear in string three
    for (size_t k = 0; k < three.length(); k++)
    {
        if (find(temp.begin(), temp.end(), three[k]) != temp.end())
        {
            out = three[k];
            break;
        }
    }
    return out;
}

int main()
{
    fstream stream;

    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";
        int sum;

        // PART 1
        string trio[3];
        int n = 0;

        while (getline(stream, line))
        {
            // PART 1
            // sum += total_for_line(line);

            // PART 2
            trio[n] = line;
            ++n;
            if (n == 3)
            {
                sum += letter_to_number(get_common_letter(trio[0], trio[1], trio[2]));
                n = 0;
            }
        }

        cout << sum;
        stream.close(); // close the file object.
    }
}