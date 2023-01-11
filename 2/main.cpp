#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void part_one()
{
    fstream stream;

    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";
        int total = 0;

        // read data from the file object and put it into a string.
        while (getline(stream, line))
        {
            int score = 0;
            switch (line[2]) // calculate response
            {
            case 'X': // rock
                score = 1;
                switch (line[0]) // outcome
                {
                case 'A': // rock
                    score += 3;
                    break;
                case 'B': // paper
                    score += 0;
                    break;
                case 'C': // scissors
                    score += 6;
                    break;
                default:
                    break;
                }
                break;

            case 'Y': // paper
                score = 2;
                switch (line[0]) // outcome
                {
                case 'A': // rock
                    score += 6;
                    break;
                case 'B': // paper
                    score += 3;
                    break;
                case 'C': // scissors
                    score += 0;
                    break;
                default:
                    break;
                }
                break;

            case 'Z': // scissors
                score = 3;
                switch (line[0]) // outcome
                {
                case 'A': // rock
                    score += 0;
                    break;
                case 'B': // paper
                    score += 6;
                    break;
                case 'C': // scissors
                    score += 3;
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }

            total += score;
        }

        cout << "Total: " << total << "\n";

        stream.close(); // close the file object.
    }
}

void part_two()
{
    fstream stream;

    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";
        int total = 0;
        int score = 0;
        // read data from the file object and put it into a string.
        while (getline(stream, line))
        {
            switch (line[0]) // opponent
            {
            case 'A':            // rock
                switch (line[2]) // outcome
                {
                case 'X': // lose
                    score = 3;
                    break;
                case 'Y': // draw
                    score = 4;
                    break;
                case 'Z': // win
                    score = 8;
                    /* code */
                    break;
                default:
                    break;
                }
                break;
            case 'B':            // paper
                switch (line[2]) // outcome
                {
                case 'X': // lose
                    score = 1;
                    break;
                case 'Y': // draw
                    score = 5;
                    break;
                case 'Z': // win
                    score = 9;
                    break;
                default:
                    break;
                }
                break;
            case 'C':            // scissors
                switch (line[2]) // outcome
                {
                case 'X': // lose
                    score = 2;
                    break;
                case 'Y': // draw
                    score = 6;
                    break;
                case 'Z': // win
                    score = 7;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }

            total += score;
        }

        cout << "Total: " << total << "\n";

        stream.close(); // close the file object.
    }
}

// https://www.scaler.com/topics/cpp-read-file-line-by-line/
int main()
{
    part_two();
}