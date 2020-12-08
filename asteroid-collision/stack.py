
class Solution:
    # def asteroidCollision(self, asteroids: List[int]) -> List[int]:
    def asteroidCollision(self, asteroids):
        return asteroid_collision(asteroids)


def asteroid_collision(asteroids):
    stack = []
    i = 0
    while i < len(asteroids):
        # Cases:
        # - empty stack? push it on
        # - not heading towards each other? push it on
        # - stack wins? increment index
        # - input wins? pop stack and continue without increment
        # - opposite values? pop stack and increment
        asteroid = asteroids[i]
        if len(stack) == 0:
            stack.append(asteroid)
            i += 1
            continue

        top = stack[-1]
        if not (top > 0 and asteroid < 0):
            stack.append(asteroid)
            i += 1
        elif abs(top) > abs(asteroid):
            i += 1
        elif abs(asteroid) > abs(top):
            stack.pop()
        else:
            assert abs(asteroid) == abs(top)
            stack.pop()
            i += 1
        
    return stack
