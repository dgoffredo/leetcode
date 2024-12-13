#include <algorithm>
#include <cassert>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#ifdef TRACE
#include <iostream>
std::ostream& operator<<(std::ostream& stream, const std::vector<int>& nums) {
    for (const int num : nums) {
        stream << ' ' << num;
    }
    return stream;
}
#define DEBUG std::cerr
#else
struct LogIgnore {};
template <typename T>
LogIgnore operator<<(LogIgnore, const T&) { return LogIgnore{}; }
#define DEBUG for (; false;) LogIgnore{}
#endif

std::vector<int> starting_positions(std::string_view text, const std::vector<std::string>& words);

class Solution {
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
       return starting_positions(s, words); 
    }
};

#ifdef TRACE
int main() {
    std::string text;
    std::cin >> text;
    std::vector<std::string> words;
    std::string word;
    while (std::cin >> word) {
        words.push_back(word);
    }

    const std::vector<int> results = Solution{}.findSubstring(text, words);
    std::cerr << "\nresults:" << results << '\n';
}
#endif

struct WordInfo {
    int index;
    int count;
};

void find_words(
        std::vector<int>& ids, // output
        std::string_view text,
        const std::unordered_map<std::string_view, WordInfo>& word_id,
        int word_size) {
    const int n = ids.size();
    for (int i = 0; i < n; ++i) {
        auto found = word_id.find(text.substr(i * word_size, word_size));
        if (found == word_id.end()) {
            ids[i] = -1;
        } else {
            ids[i] = found->second.index;
        }
    }
}

void find_permutations(
        std::vector<int>& results, // output
        std::vector<int>& counts, // scratch
        const std::vector<int>& desired_counts,
        int n_words,
        int word_size,
        int gap,
        int offset,
        std::vector<int>::const_iterator begin,
        std::vector<int>::const_iterator end) {
    assert(counts.size() == desired_counts.size());
    
    // `deficits` is the number of elements in `counts` that are below the
    // corresponding elements in `desired_counts`.
    int deficits = counts.size();
    // `excess` is whether exactly one element in `counts` is greater than its
    // corresponding element in `desired_counts`.
    bool excess = false;

    // The sliding window is `[b, e)`.
    auto b = begin;
    auto e = begin;

    const auto remove = [&](int i) {
        if (desired_counts[i] == counts[i]) {
            ++deficits;
        } else if (desired_counts[i] == counts[i] - 1) {
            excess = false;
        }
        --counts[i];
    };

    const auto add = [&](int i) {
        if (desired_counts[i] == counts[i]) {
            excess = true;
        } else if (desired_counts[i] == counts[i] + 1) {
            --deficits;
        }
        ++counts[i];
    };

    const auto shrink = [&]() -> bool {
        if (b + 1 == e) {
            return false;
        }
        remove(*b);
        ++b;
        return true;
    };

    const auto expand = [&]() -> bool {
        if (e == end || e - b == n_words) {
            return false;
        }
        add(*e);
        ++e;
        return true;
    };

    const auto slide = [&]() -> bool {
        if (e == end) {
            return false;
        }
        remove(*b);
        ++b;
        add(*e);
        ++e;
        return true;
    };

    for (;;) {
        if (excess) {
            if (!(shrink() || slide())) {
                return;
            }
        } else if (deficits != 0) {
            if (!(expand() || slide())) {
                return;
            }
        } else {
            // We found a permutation.
            results.push_back((b - begin + offset) * word_size + gap);
            if (!slide()) {
                return;
            }
        }
    }
}
            
std::vector<int> starting_positions(std::string_view text, const std::vector<std::string>& words) {
    // the calculated starting positions
    std::vector<int> results;

    // Note that there can be duplicate words.
    // `n_words` is the total number of words.
    // `word_info.size()` is the number of distinct words.
    const int n_words = words.size();
    const int word_size = words[0].size();

    if (word_size > int(text.size())) {
        return results;
    }

    std::unordered_map<std::string_view, WordInfo> word_info;
    int i = 0;
    for (const std::string& word : words) {
        auto found = word_info.find(word);
        if (found != word_info.end()) {
            ++found->second.count;
        } else {
            word_info.emplace(word, WordInfo{.index = i++, .count = 1});
        }
    }

    std::vector<int> desired_counts(word_info.size());
    for (const auto& [word, info] : word_info) {
        (void)word;
        desired_counts[info.index] = info.count;
        DEBUG << "There are " << info.count << " instances of: " << word << '\n';
    }

    DEBUG << "desired_counts: " << desired_counts << '\n';

    // `ids` will be the matches of `words` within `text`.
    // Each element is either an `index` from `word_info` or `-1` meaning
    // "no match."
    std::vector<int> ids(text.size() / word_size, -1);
 
    // how many of each word are encountered
    std::vector<int> counts(word_info.size(), 0);

    const auto valid_id = [](int i) { return i != -1; };

    // Each word has length `word_size`, and we're looking for non-overlapping
    // occurrences in `text`.
    // Simplest way is to consider each of the `word_size` suffixes of `text`.
    for (int gap = 0; gap < word_size; ++gap) {
        DEBUG << "gap=" << gap << '\n';
        find_words(ids, text.substr(gap, (text.size()  - gap) / word_size * word_size), word_info, word_size);
        DEBUG << "after find_words, ids:" << ids << '\n';
        // Iterate over all contiguous ranges of matches.
        using Iter = std::vector<int>::iterator;
        for (Iter end, begin = std::find_if(ids.begin(), ids.end(), valid_id); begin != ids.end(); begin = std::find_if(end, ids.end(), valid_id)) {
            end = std::find(begin, ids.end(), -1);
            DEBUG << "Examining range [" << (begin - ids.begin()) << ", " << (end - ids.begin()) << ")\n";
            if (end - begin < n_words) {
                // There aren't enough words in this range.
                continue;
            }
            find_permutations(results, counts, desired_counts, n_words, word_size, gap, begin - ids.begin(), begin, end);
            std::fill(counts.begin(), counts.end(), 0);
        }
        std::fill(ids.begin(), ids.end(), -1);
    }

    return results;
}

