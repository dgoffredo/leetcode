#include <array>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

class AlphaCounts {
    std::array<int, 26> counts;

 public:
   AlphaCounts()
   : counts() {}

   void increment(char letter) {
       ++counts[letter - 'a'];
   }

   std::string key() const {
       std::string result;
       for (std::size_t i = 0; i < counts.size(); ++i) {
           if (counts[i] == 0) {
                continue;
           }
           const char letter = 'a' + i;
           result += letter;
           result += std::to_string(counts[i]);
       }
       return result;
   }
};

std::vector<std::vector<std::string>> group_anagrams(const std::vector<std::string>& words) {
    std::unordered_map<std::string, std::vector<std::string>> anagrams_by_key;
    for (const std::string& word : words) {
        AlphaCounts counts;
        for (const char letter : word) {
            counts.increment(letter);
        }
        anagrams_by_key[counts.key()].push_back(word);
    }

    std::vector<std::vector<std::string>> result;
    for (auto& [key, anagrams] : anagrams_by_key) {
        result.push_back(std::move(anagrams));
    }

    return result;
}

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& words) {
        return group_anagrams(words);
    }
};
