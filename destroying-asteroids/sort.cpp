#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
      sort(asteroids.begin(), asteroids.end());
      long long planet_mass = mass;
      for (int asteroid_mass : asteroids) {
        if (asteroid_mass > planet_mass) {
          return false;
        }
        planet_mass += asteroid_mass;
      }
      return true;
    }
};
