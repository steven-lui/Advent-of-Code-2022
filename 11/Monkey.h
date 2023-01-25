#include <vector>
#include <tuple>
#include <string>
#include <iostream>

struct Monkey
{
public:
    std::vector<int64_t> items;
    // operator, operand
    std::pair<std::string, std::string> worry_operation;
    int test_value;
    // first:true, second:false
    std::pair<Monkey *, Monkey *> thrown_to;
    int inspect_count = 0;
    int modulo;

    void simulate()
    {
        if (items.empty())
        {
            return;
        }

        // run through item list
        for (int n = 0; n < items.size(); n++, inspect_count++)
        {
            // inspect and lower worry
            int new_worry = inspect(items.at(n));

            // send to new monkey
            if (test(new_worry))
            {
                thrown_to.first->items.push_back(new_worry);
            }
            else
            {
                thrown_to.second->items.push_back(new_worry);
            }
        }

        // clear the item list now all have been inspected
        items.clear();
    }

private:
    bool test(int item)
    {
        return (item % test_value == 0);
    }

    // Operation shows how your worry level changes as that monkey inspects an item
    // /3, %modulo
    int inspect(int old_worry)
    {
        int64_t operand = (worry_operation.second == "old") ? old_worry : stoi(worry_operation.second);
        int64_t output = (worry_operation.first == "*") ? (operand * old_worry) : (operand + old_worry);
        return output % modulo;
    }
};
