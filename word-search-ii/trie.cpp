#include <array>
#include <cctype>
#include <memory>
#include <string>
#include <vector>

// We can mark a grid cell as "visited" by making it upper case, as an
// optimization. Then unmark it by making it lower case again.

bool is_lower(char letter) {
    return letter >= 'a' && letter <= 'z';
}

// The need for these wrappers is one of the dumbest things about C++.

char to_upper(unsigned char letter) {
    return std::toupper(letter);
}

char to_lower(unsigned char letter) {
    return std::tolower(letter);
}

struct PrefixTrieNode {
    std::string *match = nullptr;
    std::array<PrefixTrieNode*, 26> children = {};

    PrefixTrieNode*& operator[](char letter) {
        return children[letter - 'a'];
    }
};

struct PrefixTrieDeleter {
    void operator()(PrefixTrieNode *node) const {
        if (node == nullptr) {
            return;
        }

        std::vector<PrefixTrieNode*> stack = {node};
        do {
            auto node = stack.back();
            stack.pop_back();    
            for (auto *child : node->children) {
                if (child) {
                    stack.push_back(child);
                }
            }
            delete node;
        } while (!stack.empty());
    }
};

using PrefixTrie = std::unique_ptr<PrefixTrieNode, PrefixTrieDeleter>;

void add_word_to_trie(PrefixTrieNode& trie, std::string& word) {
    PrefixTrieNode *node = &trie;
    for (const char letter : word) {
        PrefixTrieNode*& child = (*node)[letter];
        if (child == nullptr) {
            child = new PrefixTrieNode();
        }
        node = child;
    }
    if (node->match == nullptr) {
        node->match = &word;
    }
}

PrefixTrie build_prefix_trie(std::vector<std::string>& words) {
    auto trie = PrefixTrie(new PrefixTrieNode());
    for (std::string& word : words) {
        add_word_to_trie(*trie, word);
    }
    return trie;
}

std::vector<std::string> find_words(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
    std::vector<std::string> found;
    PrefixTrie trie = build_prefix_trie(words);
    const int rows = board.size();
    const int cols = board[0].size();
    
    const auto visit = [&](int r, int c, PrefixTrieNode* node, auto& recur) {
        node = (*node)[board[r][c]];
        if (node == nullptr) {
            return;
        }
        if (node->match) {
            // We found a word.
            found.push_back(std::move(*node->match));
            // Remove the match from the trie so we don't "find" it again.
            node->match = nullptr;
        }

        // Mark this square as "visited."
        board[r][c] = to_upper(board[r][c]);
        
        // Examine eligible neighbors.
        // above:
        if (r > 0 && is_lower(board[r - 1][c])) {
            recur(r - 1, c, node, recur);
        }
        // below:
        if (r < rows - 1 && is_lower(board[r + 1][c])) {
            recur(r + 1, c, node, recur);
        }
        // leftward:
        if (c > 0 && is_lower(board[r][c - 1])) {
            recur(r, c - 1, node, recur);
        }
        // rightward:
        if (c < cols - 1 && is_lower(board[r][c + 1])) {
            recur(r, c + 1, node, recur);
        }

        // Unmark this square.
        board[r][c] = to_lower(board[r][c]);
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // (r, c) is the starting point. Snake around the grid looking for words.
            visit(r, c, trie.get(), visit);
        }
    }
    return found;
}

class Solution {
public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
        return find_words(board, words);
    }
};
