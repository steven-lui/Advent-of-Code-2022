#include <string>
#include <vector>

std::vector<std::string> split_string(std::string str, std::string delimiter = " ")
{
    int start = 0;
    int end = str.find(delimiter);
    std::vector<std::string> output;

    while (end != -1)
    {
        output.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    output.push_back(str.substr(start, end - start));
    return output;
}