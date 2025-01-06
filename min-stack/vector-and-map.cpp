#include <map>
#include <vector>

class MinStack {
    std::vector<int> stack;
    std::map<int, int> frequencies;

public:
    void push(int value) {
        stack.push_back(value);
        ++frequencies[value];   
    }
    
    void pop() {
        const auto iter = frequencies.find(stack.back());
        if (iter->second == 1) {
            frequencies.erase(iter);
        } else {
            --iter->second;
        }
        stack.pop_back();
    }
    
    int top() {
        return stack.back();
    }
    
    int getMin() {
        return frequencies.begin()->first;
    }
};
