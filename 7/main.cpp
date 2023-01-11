#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../useful_functions.h"
#include "Node.h"

using namespace std;

int main()
{
    fstream stream;

    vector<Node *> directories;

    Node *root;
    root = getNewNode(0, "root", nullptr);
    root->children.push_back(getNewNode(0, "/", root));

    Node *current = root;

    stream.open("input.txt", ios::in);
    if (stream.is_open())
    {
        string line = "";

        while (getline(stream, line))
        {
            // command
            if (split_string(line).at(0) == "$")
            {
                // change directory
                if (split_string(line).at(1) == "cd")
                {
                    string folder = split_string(line).at(2);

                    // out
                    if (folder == "..")
                    {
                        current = current->parent;
                    }
                    // in
                    else
                    {
                        size_t i = 0;
                        bool found = false;

                        while (!found)
                        {
                            found = (current->children.at(i)->name == folder);
                            if (!found)
                                i++;
                        }

                        current = current->children.at(i);
                    }
                }
            }
            // file (folders are 0 size files)
            else
            {
                string name = (split_string(line).at(1));
                int size = 0;

                if (split_string(line).at(0) != "dir") // if a file
                    size = stoi(split_string(line).at(0));

                current->children.push_back(getNewNode(size, name, current));

                if (split_string(line).at(0) == "dir") // add folder to directories
                    directories.push_back(current->children.back());
            }
        }

        stream.close(); // close the file object.
    }

    sort(directories.begin(), directories.end(), less_than_size());

    // PART ONE: TOTAL SIZE OF DIRECTORIES UP TO 100000
    int output;
    for (size_t i = 0; i < directories.size(); i++)
    {
        int sum = sumNodes(directories.at(i));
        if (sum <= 100000)
            output += sum;
    }
    cout << output << endl;

    // PART TWO: SMALLEST DIRECTORY THAT IS >30000000
    int space = 70000000 - sumNodes(root);
    int i = 0;
    bool found = false;
    int sum = 0;

    while (!found)
    {
        sum = sumNodes(directories.at(i));
        if ((space + sum) > 30000000)
            found = true;
        ++i;
    }

    // the space it frees up
    cout << sum << endl;
}