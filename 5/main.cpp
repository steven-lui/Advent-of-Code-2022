#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include "../useful_functions.h"

using namespace std;

void print_top_of_grid(vector<vector<char>> grid)
{
    for (size_t i = 0; i < grid.size(); i++)
    {
        cout << grid.at(i).back();
    }
    cout << endl;
}

vector<vector<char>> text_to_grid(vector<string> input)
{
    vector<vector<char>> output;

    // remove redundant lines
    input.pop_back();
    input.pop_back();

    int raw_line_length = input.front().size();
    int number_of_columns = (raw_line_length + 1) / 4;

    // create output dimensions
    for (size_t i = 0; i < number_of_columns; i++)
    {
        output.push_back(vector<char>());
    }

    // iterate through input to add to output
    for (size_t i = 0; i < input.size(); i++)
    {
        string line = input.at(i);

        // go through the string to find characters
        size_t char_position = 1;
        while (char_position < raw_line_length)
        {
            // get character
            char c = line.at(char_position);

            // insert to position
            if (c != ' ')
            {
                int pos = char_position == 1 ? 0 : (char_position - 1) / 4;
                output.at(pos).insert(output.at(pos).begin(), c);
            }
            char_position += 4;
        }
    }

    return output;
}

void move_crate(vector<vector<char>> &grid, tuple<int, int, int> instruction)
{
    int number_of_crates = get<0>(instruction);
    int position_one = get<1>(instruction) - 1;
    int position_two = get<2>(instruction) - 1;

    for (int i = 0; i < number_of_crates; ++i)
    {
        char c = grid.at(position_one).back();
        grid.at(position_one).pop_back();
        grid.at(position_two).push_back(c);
    }
}

void move_stack(vector<vector<char>> &grid, tuple<int, int, int> instruction)
{
    int number_of_crates = get<0>(instruction);
    int position_one = get<1>(instruction) - 1;
    int position_two = get<2>(instruction) - 1;

    vector<char> temporary_stack;

    // create stack
    for (int i = 0; i < number_of_crates; ++i)
    {
        char c = grid.at(position_one).back();
        grid.at(position_one).pop_back();
        temporary_stack.push_back(c);
    }

    // push stack in order
    for (size_t i = 0; i < number_of_crates; i++)
    {
        grid.at(position_two).push_back(temporary_stack.back());
        temporary_stack.pop_back();
    }
}

int main()
{
    fstream stream;

    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";
        vector<vector<char>> grid;
        vector<tuple<int, int, int>> i_list;

        bool isGrid = true;
        vector<string> s_grid;
        while (getline(stream, line))
        {
            // start by holding onto the head
            if (isGrid)
            {
                s_grid.push_back(line);
            }

            // prepare the instruction set
            else
            {
                if (line != "")
                {
                    vector<string> instr = split_string(line);
                    int count = stoi(instr.at(1));
                    int start = stoi(instr.at(3));
                    int end = stoi(instr.at(5));
                    i_list.push_back(tuple<int, int, int>(count, start, end));
                }
            }

            // check for empty line which divides the head and instruction
            if (line == "")
            {
                isGrid = false;
            }
        }

        // construct grid
        grid = text_to_grid(s_grid);

        // apply instructions
        for (size_t i = 0; i < i_list.size(); i++)
        {
            move_crate(grid, i_list.at(i));
            move_stack(grid, i_list.at(i)); // part two
        }

        print_top_of_grid(grid);

        stream.close(); // close the file object.
    }
}
