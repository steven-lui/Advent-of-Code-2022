#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>
#include "../useful_functions.h"

// 20th, 60th, 100th, 140th, 180th, and 220th cycles
void strength_sum_check(int cycle, int reg_x, int &strength_sum)
{
    if (cycle % 40 == 20)
        strength_sum += reg_x * cycle;
}

void print_image(bool image[6][40])
{
    for (size_t y = 0; y < 6; y++)
    {
        for (size_t x = 0; x < 40; x++)
            std::cout << (image[y][x] ? '#' : '.');

        std::cout << std::endl;
    }
}

// The pixel is on if the sprite overlaps the pixel position
bool is_pixel_on(int cycle, int reg_x)
{
    int pixel = (cycle % 40) - 1;
    for (int i = -1; i <= 1; i++)
    {
        if ((reg_x + i) == pixel)
            return true;
    }

    return false;
}

int main()
{
    std::fstream stream;
    stream.open("input.txt", std::ios::in);

    int reg_x = 1;
    int cycle = 1;

    int strength_sum = 0;

    bool image[6][40] = {false};

    if (stream.is_open())
    {
        std::string line = "";

        while (getline(stream, line))
        {
            // CRT draws pixel in position on begin execution
            image[cycle / 40][(cycle % 40) - 1] = is_pixel_on(cycle, reg_x);

            // noop takes one cycle to complete. It has no other effect.
            cycle++;

            strength_sum_check(cycle, reg_x, strength_sum);

            // addx, runs an additional cycle before adding the value
            if (line != "noop")
            {
                // CRT draws pixel in position on during execution
                image[cycle / 40][(cycle % 40) - 1] = is_pixel_on(cycle, reg_x);

                // apply operation
                cycle++;
                reg_x += std::stoi(split_string(line)[1]);

                strength_sum_check(cycle, reg_x, strength_sum);
            }

            // CRT draws pixel in position on after execution
            image[cycle / 40][(cycle % 40) - 1] = is_pixel_on(cycle, reg_x);
        }

        stream.close();
    }

    // PART ONE: SIGNAL STRENGTH
    std::cout << strength_sum << std::endl;

    // PART TWO: PRINT IMAGE
    print_image(image);

    return 0;
};