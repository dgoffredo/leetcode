#include <algorithm>
#include <string>

std::string reverse_words(const std::string& str) {
    const auto not_space = [](char ch) { return ch != ' '; };

    const auto end = str.rend();
    auto iter = std::find_if(str.rbegin(), end, not_space);

    std::string result;
    while (iter != end) {
        const auto word_end = std::find(iter, end, ' ');
        if (!result.empty()) {
            result += ' ';
        }
        result.append(word_end.base(), iter.base());
        iter = std::find_if(word_end, end, not_space);
    }

    return result;
}

class Solution {
public:
    std::string reverseWords(std::string str) {
        return reverse_words(str);
    }
};
