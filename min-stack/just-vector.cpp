#include <algorithm>
#include <vector>

class MinStack {
    struct Entry {
        int value;
        int min_from_here;
    };

    std::vector<Entry> stack;

public:
    void push(int value) {
        if (stack.empty()) {
            stack.push_back(Entry{.value=value, .min_from_here=value});
            return;
        }
        stack.push_back(Entry{
            .value=value,
            .min_from_here=std::min(stack.back().min_from_here, value)});
    }
    
    void pop() {
        stack.pop_back();
    }
    
    int top() {
        return stack.back().value;
    }
    
    int getMin() {
        return stack.back().min_from_here;
    }
};
