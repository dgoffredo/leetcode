#include <cassert>
#include <list>
#include <unordered_map>

class LRUCache {
    struct Record {
        int value;
        std::list<int>::const_iterator access;
    };
    const std::unordered_map<int, Record>::size_type capacity;
    std::unordered_map<int, Record> records;
    std::list<int> keys_by_access;

public:
    explicit LRUCache(int capacity)
    : capacity(capacity) {
    }
    
    int get(int key) {
        const auto found = records.find(key);
        if (found == records.end()) {
            return -1;
        }
        const auto& [value, access] = found->second;
        // Move the `access` iterator to the end, since it has now been
        // recently accessed (so will be last to be evicted).
        keys_by_access.splice(keys_by_access.end(), keys_by_access, access);
        return value;
    }
    
    void put(int key, int new_value) {
        const auto found = records.find(key);
        if (found != records.end()) {
            auto& [value, access] = found->second;
            value = new_value;
            // Move the `access` iterator to the end, since it has now been
            // recently accessed (so will be last to be evicted).
            keys_by_access.splice(keys_by_access.end(), keys_by_access, access);
            return;
        }

        // This is a new entry.
        keys_by_access.push_back(key);
        records.emplace(key, Record{new_value, std::next(keys_by_access.end(), -1)});

        // Maybe evict an entry.
        if (records.size() > capacity) {
            assert(records.size() == capacity + 1);
            const int key_to_delete = keys_by_access.front();
            keys_by_access.pop_front();
            records.erase(key_to_delete);
        }
    }
};
