
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>  // debugging only
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// std::ostream& debug = std::cout;

class Dummy {
};

template <typename T>
Dummy operator<<(Dummy, const T&) {
    return Dummy();
}

Dummy debug;

std::vector<int> minimalSetCover(
    const std::vector<std::string>&              universe,
    const std::vector<std::vector<std::string>>& subsets);
                                

// leetcode.com boilerplate
class Solution {
public:
    std::vector<int> smallestSufficientTeam(
        std::vector<std::string>&              req_skills,
        std::vector<std::vector<std::string>>& people) {
        return minimalSetCover(req_skills, people);
    }
};

template <typename MAP>
std::vector<typename MAP::key_type> keys(
    std::vector<typename MAP::key_type>& storage,
    const MAP&                           map) {

    storage.clear();
    storage.reserve(map.size());

    for (const auto& item : map) {
        storage.push_back(item.first);
    }

    return storage;
}

std::vector<int> minimalSetCover(
    const std::vector<std::string>&              universe,
    const std::vector<std::vector<std::string>>& subsets) {

    typedef std::bitset<16> ElementSet;
    // and then std::vector<int>, the return type, is a set of subset indices.

    assert(std::ceil(std::log2(universe.size())) <= 16);

    std::unordered_map<std::string, int> elementIndices;
    for (int i = 0; i < int(universe.size()); ++i) {
        elementIndices[universe[i]] = i;
    }

    // `minimalCovers` keeps track of which subsets cover a particular
    // `ElementSet`.  `keysStorage` is used to avoid having to reallocate a
    // vector of keys every time around the loop.
    std::unordered_map<ElementSet, std::vector<int> > minimalCovers;
    minimalCovers.emplace(0, std::vector<int>());
    std::vector<ElementSet> keysStorage;

    for (int i = 0; i < int(subsets.size()); ++i) {
        const std::vector<std::string>& subset = subsets[i];
        ElementSet                               subsetMask;
        for (int j = 0; j < int(subset.size()); ++j) {
            subsetMask[elementIndices[subset[j]]] = true;
        }

        for (const ElementSet& key : keys(keysStorage, minimalCovers)) {
            const std::vector<int>& participants =
                minimalCovers.find(key)->second;

            const ElementSet combined = key | subsetMask;
            debug << "examining subset " << i << ": " << subsetMask
                      << " | " << key << " -> " << combined << "\n";

            if (key == combined) {
                continue;  // nothing gained
            }

            // If the combined skill set isn't yet in `minimalCovers`, or if
            // it's already there but we have a more minimal cover, then add
            // a new entry (or overwrite the existing).
            const auto found = minimalCovers.find(combined);
            if (found == minimalCovers.end()) {
                // Add a new entry.
                std::vector<int>& newParticipants = minimalCovers[combined];
                newParticipants.reserve(participants.size() + 1);
                newParticipants.insert(newParticipants.end(),
                                       participants.begin(),
                                       participants.end());
                newParticipants.push_back(i);
                continue;
            }
            
            std::vector<int>& oldParticipants = found->second;
            if (oldParticipants.size() > participants.size() + 1) {
                // Overwrite the existing entry.
                oldParticipants.clear();
                oldParticipants.reserve(participants.size() + 1);
                oldParticipants.insert(oldParticipants.end(),
                                       participants.begin(),
                                       participants.end());
                oldParticipants.push_back(i);
            }
        }
    }

    for (const auto& item : minimalCovers) {
        debug << item.first << ": ";
        const auto& cover = item.second;
        for (int index : cover) {
            debug << index << " ";
        }
        debug << "\n";
    }

    const ElementSet all((1 << universe.size()) - 1);
    return minimalCovers.find(all)->second;
}
                                