#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

using namespace std;

tuple<int, int> get_section_range(string input)
{
    return tuple<int, int>{stoi(input.substr(0, input.find("-"))),
                           stoi(input.substr(input.find("-") + 1, input.length() - 1))};
}

bool in_range(tuple<int, int> one, tuple<int, int> two)
{
    return (
        (get<0>(one) <= get<0>(two)) &&
        (get<1>(one) >= get<1>(two)));
}

bool part_range(tuple<int, int> one, tuple<int, int> two)
{
    return (
        (get<1>(one) >= get<0>(two)) &&
        (get<0>(one) <= get<1>(two)));
}

int main()
{
    fstream stream;

    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";
        int n;

        while (getline(stream, line))
        { // read data from the file object and put it into a string.
            tuple<int, int> one = get_section_range(line.substr(0, line.find(",")));
            tuple<int, int> two = get_section_range(line.substr(line.find(",") + 1, line.length() - 1));

            // if (in_range(one, two) || in_range(two, one))
            if (part_range(one, two) || part_range(two, one))
                ++n;
        }

        cout << n;

        stream.close(); // close the file object.
    }
}