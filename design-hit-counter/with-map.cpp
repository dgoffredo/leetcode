#include <cassert>
#include <iostream>
#include <map>

// `std::cerr` is debug logging. Delete all of that before submitting.

class HitCounter {
  static constexpr int horizon_seconds = 300; // five minutes
  // time (seconds) -> number of hits at or before that time
  std::map<int, int> counts;
  int hits_beyond_horizon = 0;

 public:
   void hit(int when_seconds) {
    std::cerr << "hit(" << when_seconds << ")\n";
    std::cerr << "    before: " << hits_beyond_horizon << ", [";
    for (const auto& [when, count] : counts) {
      std::cerr << ' ' << when << ':' << count;
    }
    std::cerr << " ]\n";
    const auto found = counts.find(when_seconds);
    if (found != counts.end()) {
      ++found->second;
      std::cerr << "    after: " << hits_beyond_horizon << ", [";
      for (const auto& [when, count] : counts) {
        std::cerr << ' ' << when << ':' << count;
      }
      std::cerr << " ]\n";
      return;
    }
    const int count_before = counts.empty() ? 0 : counts.rbegin()->second;
    counts.emplace(when_seconds, 1 + count_before);

    // Trim off entries that are beyond the horizon.
    const auto range_end = counts.lower_bound(when_seconds - horizon_seconds);
    if (counts.begin() != range_end) {
      hits_beyond_horizon = std::next(range_end, -1)->second;
    }
    counts.erase(counts.begin(), range_end);

    std::cerr << "    after: " << hits_beyond_horizon << ", [";
    for (const auto& [when, count] : counts) {
      std::cerr << ' ' << when << ':' << count;
    }
    std::cerr << " ]\n";
   }

   int getHits(int at_or_before_when) {
     std::cerr << "getHits(" << at_or_before_when << ")\n";
     std::cerr << "    horizon key = " << (at_or_before_when - horizon_seconds) << '\n';
     const auto horizon = counts.lower_bound(at_or_before_when - horizon_seconds);
     std::cerr << "    horizon index = " << std::distance(counts.begin(), horizon) << '\n';
     int offset;
     if (horizon == counts.begin() && horizon->first > at_or_before_when - horizon_seconds) {
       offset = hits_beyond_horizon;
     } else if (horizon == counts.end()) {
       std::cerr << "    offset=? result=0\n";
       return 0;
     } else {
      offset = horizon->second;
     }

     assert(!counts.empty());
     int result = counts.rbegin()->second - offset;
     std::cerr << "    offset=" << offset << " result=" << result << '\n';
     return result;
   }
};

int main() {
  HitCounter counter;

  counter.hit(1);
  counter.hit(2);
  counter.hit(3);
  
  int hits;
  // get hits at timestamp 4, should return 3.
  hits = counter.getHits(4);
  std::cout << __LINE__ << ": " << hits << '\n';

  counter.hit(300);

  // get hits at timestamp 300, should return 4.
  hits = counter.getHits(300);
  std::cout << __LINE__ << ": " << hits << '\n';

  // get hits at timestamp 301, should return 3.
  hits = counter.getHits(301);
  std::cout << __LINE__ << ": " << hits << '\n';

  counter.hit(303);
  // should return 2
  hits = counter.getHits(303);
  std::cout << __LINE__ << ": " << hits << '\n';

  // should return 1
  hits = counter.getHits(600);
  std::cout << __LINE__ << ": " << hits << '\n';
}
