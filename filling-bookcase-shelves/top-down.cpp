#include <algorithm>
#include <cassert>
#include <cstdint>
#include <unordered_map>
#include <vector>

union Key {
  std::uint32_t key;
  struct {
    unsigned i : 10;
    unsigned width_remaining : 10;
    unsigned shelf_height : 10;
  } fields;
};

int shortest_bookcase(
    std::unordered_map<std::uint32_t, int>& cache,
    Key key,
    const std::vector<std::vector<int>>& books,
    int width) {
 const auto entry = cache.find(key.key);
 if (entry != cache.end()) {
   return entry->second;
 }

 const auto [i, width_remaining, shelf_height] = key.fields;
 if (i == books.size()) {
   return shelf_height;
 }

 const auto& book = books[i];
 assert(book.size() == 2);
 const int thickness = book[0];
 const int height = book[1];

 Key new_shelf_key;
 new_shelf_key.fields.i = i + 1;
 new_shelf_key.fields.width_remaining = width - thickness;
 new_shelf_key.fields.shelf_height = height;
 const int new_shelf = shelf_height + shortest_bookcase(cache, new_shelf_key, books, width);

 if (width_remaining < thickness) {
   cache.emplace(key.key, new_shelf);
   return new_shelf;
 }

 Key same_shelf_key;
 same_shelf_key.fields.i = i + 1;
 same_shelf_key.fields.width_remaining = width_remaining - thickness;
 same_shelf_key.fields.shelf_height = std::max<unsigned>(shelf_height, height);
 const int same_shelf = shortest_bookcase(cache, same_shelf_key, books, width);

 const int shortest = std::min(new_shelf, same_shelf);
 cache.emplace(key.key, shortest);
 return shortest;
}

int shortest_bookcase(const std::vector<std::vector<int>>& books, int width) {
  std::unordered_map<std::uint32_t, int> cache;
  Key start;
  start.fields.i = 0;
  start.fields.width_remaining = width;
  start.fields.shelf_height = 0;
  return shortest_bookcase(cache, start, books, width);
}

class Solution {
public:
    int minHeightShelves(std::vector<std::vector<int>>& books, int shelfWidth) {
        return shortest_bookcase(books, shelfWidth);
    }
};

