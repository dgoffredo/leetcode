#include <set>

class SmallestInfiniteSet {
  std::set<int> restored;
  int watermark = 1; // next value to pop if `restored` is empty

public:
    int popSmallest() {
      if (restored.empty()) {
        return watermark++;
      }

      const int result = *restored.begin();
      restored.erase(restored.begin());
      return result;
    }

    void addBack(int num) {
      if (num >= watermark) {
        return;
      }
      restored.insert(num);
    }
};
