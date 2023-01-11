#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool is_tree_biggest(int tree, vector<int> line)
{
    sort(line.begin(), line.end());
    return tree > line.back();
}

bool left(int x, int y, vector<vector<int>> grid)
{
    vector<int> row;
    for (size_t i = 0; i < x; i++)
        row.push_back(grid.at(y).at(i));

    return is_tree_biggest(grid.at(y).at(x), row);
}

bool right(int x, int y, vector<vector<int>> grid)
{
    vector<int> row;
    for (size_t i = x + 1; i < grid.at(y).size(); i++)
        row.push_back(grid.at(y).at(i));

    return is_tree_biggest(grid.at(y).at(x), row);
}

bool up(int x, int y, vector<vector<int>> grid)
{
    vector<int> column;
    for (size_t i = 0; i < y; i++)
        column.push_back(grid.at(i).at(x));

    return is_tree_biggest(grid.at(y).at(x), column);
}

bool down(int x, int y, vector<vector<int>> grid)
{
    vector<int> column;
    for (size_t i = y + 1; i < grid.size(); i++)
        column.push_back(grid.at(i).at(x));

    return is_tree_biggest(grid.at(y).at(x), column);
}

int score_left(int x, int y, vector<vector<int>> grid)
{
    int score = 0;
    int i = x;
    bool hasSight = true;

    while (hasSight && i > 0)
    {
        --i;
        ++score;
        hasSight = grid.at(y).at(x) > grid.at(y).at(i);
    }

    return score;
}

int score_right(int x, int y, vector<vector<int>> grid)
{
    int score = 0;
    int i = x;
    bool hasSight = true;

    while (hasSight && i < grid.at(y).size() - 1)
    {
        ++i;
        ++score;
        hasSight = grid.at(y).at(x) > grid.at(y).at(i);
    }

    return score;
}

int score_up(int x, int y, vector<vector<int>> grid)
{
    int score = 0;
    int i = y;
    bool hasSight = true;

    while (hasSight && i > 0)
    {
        --i;
        ++score;
        hasSight = grid.at(y).at(x) > grid.at(i).at(x);
    }

    return score;
}

int score_down(int x, int y, vector<vector<int>> grid)
{
    int score = 0;
    int i = y;
    bool hasSight = true;

    while (hasSight && i < grid.size() - 1)
    {
        ++i;
        ++score;
        hasSight = grid.at(y).at(x) > grid.at(i).at(x);
    }

    return score;
}

int scenic_score(int x, int y, vector<vector<int>> grid)
{
    int score = 1;
    score *= score_left(x, y, grid);
    score *= score_right(x, y, grid);
    score *= score_up(x, y, grid);
    score *= score_down(x, y, grid);
    return score;
}

int main()
{
    fstream stream;
    vector<vector<int>> grid;
    size_t y1 = 0;
    int visible = 0;

    // create grid
    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";

        while (getline(stream, line))
        {
            grid.push_back(vector<int>());
            for (size_t i = 0; i < line.length(); i++)
            {
                grid.at(y1).push_back(line.at(i));
            }
            ++y1;
        }

        stream.close();
    }

    // fixed size now, calc some stuff
    const size_t x = grid.back().size();
    const size_t y = y1;

    // PART ONE: VISIBLE TREES FROM THE OUTSIDE
    // visible = (2 * x) + ((y - 2) * 2);
    // for (size_t i = 1; i < (y - 1); i++)
    // {
    //     for (size_t j = 1; j < (x - 1); j++)
    //     {
    //         if (left(j, i, grid) || right(j, i, grid) || up(j, i, grid) || down(j, i, grid))
    //             ++visible;
    //     }
    // }
    // cout << visible << endl;

    // PART TWO SCENIC SCORE
    // consider only inner trees
    int top_score = 0;
    int cur_score;
    for (size_t i = 1; i < (y - 1); i++)
    {
        for (size_t j = 1; j < (x - 1); j++)
        {
            cur_score = scenic_score(j, i, grid);
            if (cur_score > top_score)
                top_score = cur_score;
        }
    }
    cout << top_score << endl;
}