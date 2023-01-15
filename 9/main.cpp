#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <set>
#include <array>
#include <tuple>
#include "../useful_functions.h"

int clamp(int value, int min, int max) { return std::min(std::max(value, min), max); }

// Structure representing a Vec2 (pair of ints)
struct Vec2 : std::pair<int, int>
{
    using std::pair<int, int>::pair;

    // We can subtract Vec2s
    Vec2 operator-(Vec2 &operand) { return {first - operand.first, second - operand.second}; }
    // We can add Vec2s
    Vec2 operator+(Vec2 &operand) { return {first + operand.first, second + operand.second}; }

    // We can find the distance between Vec2s (returning this as an integer assumes that all 8 cardinal directions are the same distance)
    int distance(Vec2 &operand)
    {
        auto toward = (*this) - operand;
        return std::sqrt(toward.first * toward.first + toward.second * toward.second);
    }
};

template <int Length>
struct Rope
{
    std::array<Vec2, Length> knots;
    Vec2 &head() { return knots.front(); }
    Vec2 &tail() { return knots.back(); }

    Rope()
    {
        knots = {Vec2(), Vec2()};
    }

    void simulate()
    {
        // Go down the rope treating each pair of knots as a head and tail pair and simulating them
        for (int i = 1; i < Length; i++)
            simulateTail(knots[i - 1], knots[i]);
    }

private:
    // Assume that the head has moved one space
    void simulateTail(Vec2 &head, Vec2 &tail)
    {
        // Don't bother if they touch or overlap
        if (head.distance(tail) <= 1)
            return;

        // Get the direction the tail would need to move to get to the head
        auto target_direction = head - tail;
        target_direction.first = clamp(target_direction.first, -1, 1);
        target_direction.second = clamp(target_direction.second, -1, 1);

        // Move the tail toward the head
        tail = tail + target_direction;
    }
};

int main()
{
    std::fstream stream;
    stream.open("input.txt", std::ios::in);

    std::set<Vec2> tail_positions;

    // PART ONE: 2 KNOTS
    // PART TWO: 10 KNOTS
    Rope<10> rope;

    if (stream.is_open())
    {
        std::string line = "";

        while (getline(stream, line))
        {
            char direction = line[0];
            int steps = std::stoi(split_string(line)[1]);

            for (size_t i = 0; i < steps; i++)
            {
                // move the head
                switch (direction)
                {
                case 'R':
                    rope.head().first++;
                    break;
                case 'L':
                    rope.head().first--;
                    break;
                case 'U':
                    rope.head().second++;
                    break;
                case 'D':
                    rope.head().second--;
                    break;
                default:
                    break;
                }

                // simulate
                rope.simulate();

                // log tail movement
                tail_positions.insert(rope.tail());
            }
        }

        std::cout << tail_positions.size() << std::endl;

        stream.close();
    }

    return 0;
};