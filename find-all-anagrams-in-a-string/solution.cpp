
#include <array>
#include <cstddef>
#include <vector>
#include <string>

std::vector<int> anagramStartPositions(const std::string& subject, const std::string& pattern);

class Solution {
public:
    std::vector<int> findAnagrams(std::string s, std::string p) {
        return anagramStartPositions(s, p);
    }
};

std::vector<int> anagramStartPositions(const std::string& subject, const std::string& pattern) {
    std::vector<int> positions;
    if (subject.size() < pattern.size()) {
        return positions;
    }

    std::array<int, 26> patternFrequencies{};
    std::array<int, 26> currentFrequencies{};

    for (std::size_t i = 0; i < pattern.size(); ++i) {
        ++patternFrequencies[pattern[i] - 'a'];
        ++currentFrequencies[subject[i] - 'a'];
    }

    std::size_t currentBegin = 0;
    for (;;) {
        if (currentFrequencies == patternFrequencies) {
            positions.push_back(currentBegin);
        }

        if (currentBegin + pattern.size() == subject.size()) {
            break;
        }

        // decrement the frequency of the letter we're leaving behind
        --currentFrequencies[subject[currentBegin] - 'a'];

        // increment the frequency of the letter we're moving to
        ++currentFrequencies[subject[currentBegin + pattern.size()] - 'a'];

        ++currentBegin;
    }

    return positions;
}

#ifdef REPL
#include <iostream>

int main() {
    std::string subject;
    std::string pattern;

    std::vector<int> positions;
    while (std::cin >> subject >> pattern) {
        positions = Solution().findAnagrams(subject, pattern);
        for (const int position : positions) {
            std::cout << " " << position;
        }
        std::cout << "\n\n";
    }
}
#endif // defined(REPL)
