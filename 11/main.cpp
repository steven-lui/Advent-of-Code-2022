#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../useful_functions.h"
#include "Monkey.h"

int main()
{
    std::fstream stream;
    stream.open("input.txt", std::ios::in);

    // 20, 10000
    int rounds = 10000;

    int group_size = 8;
    Monkey monkeys[group_size];

    int counter = -1;
    if (stream.is_open())
    {
        std::string line = "";
        while (getline(stream, line))
        {
            std::vector<std::string> args = split_string(line);

            // new monkey
            if (args[0] == "Monkey")
                counter++;

            // blank lines that don't contain info
            if (args[0] == "Monkey" || args.size() == 1)
                continue;

            if (args[2] == "Starting")
            {
                for (std::string s : split_string(line.substr(18), ", "))
                    monkeys[counter].items.push_back(stoi(s));
            }
            else if (args[2] == "Operation:")
            {
                monkeys[counter].worry_operation.first = args[6];
                monkeys[counter].worry_operation.second = args[7];
            }
            else if (args[2] == "Test:")
            {
                monkeys[counter].test_value = stoi(args[5]);
            }
            // If true/false:
            else
            {
                Monkey *pointer = &monkeys[stoi(args[9])];
                args[5] == "true:" ? monkeys[counter].thrown_to.first = pointer : monkeys[counter].thrown_to.second = pointer;
            }
        }
        stream.close();
    }

    // PART TWO: LCM
    int mod = 1;
    for (int m = 0; m < group_size; m++)
        mod *= monkeys[m].test_value;
    for (int m = 0; m < group_size; m++)
        monkeys[m].modulo = mod;

    // RUN SIMULATION
    for (int r = 0; r < rounds; r++)
        for (int m = 0; m < group_size; m++)
            monkeys[m].simulate();

    // MONKEY BUSINESS
    int count[group_size];
    for (int m = 0; m < group_size; m++)
    {
        count[m] = monkeys[m].inspect_count;
        std::cout << "Monkey " << m << " inspected items " << count[m] << " times." << std::endl;
    }
    std::sort(count, count + group_size);
    std::cout << "Monkey business: " << count[group_size - 1] << " * " << count[group_size - 2] << std::endl;

    return 0;
}