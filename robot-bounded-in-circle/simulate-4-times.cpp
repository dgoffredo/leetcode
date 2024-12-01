#include <string>
#include <tuple>
#include <utility>

enum Heading {NORTH, SOUTH, EAST, WEST};

struct Robot {
  int x;
  int y;
  Heading heading;
};

Heading turn_left(Heading heading) {
  switch (heading) {
  case NORTH: return WEST;
  case SOUTH: return EAST;
  case EAST: return NORTH;
  default: return SOUTH;
  }
}

Heading turn_right(Heading heading) {
  switch (heading) {
  case NORTH: return EAST;
  case SOUTH: return WEST;
  case EAST: return SOUTH;
  default: return NORTH;
  }
}

// (x, y)
std::pair<int, int> go_straight(Robot bot) {
  switch (bot.heading) {
  case NORTH: return {bot.x, bot.y + 1};
  case SOUTH: return {bot.x, bot.y - 1};
  case EAST: return {bot.x + 1, bot.y};
  default: return {bot.x - 1, bot.y};
  }
}

Robot simulate(Robot start, const std::string& program) {
  Robot bot = start;

  for (const char instruction : program) {
    switch (instruction) {
    case 'G': {
      std::tie(bot.x, bot.y) = go_straight(bot);
    } break;
    case 'L':
      bot.heading = turn_left(bot.heading);
      break;
    default:
      bot.heading = turn_right(bot.heading);
    }
  }

  return bot;
}

bool contains_cycle(const std::string& program) {
  Robot bot = {
    .x = 0,
    .y = 0,
    .heading = NORTH
  };

  for (int i = 0; i < 4; ++i) {
    bot = simulate(bot, program);
    if (bot.x == 0 && bot.y == 0) {
      return true;
    }
  }

  return false;
}

class Solution {
public:
    bool isRobotBounded(const std::string& instructions) {
       return contains_cycle(instructions);
    }
};
