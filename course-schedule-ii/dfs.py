from typing import List


class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        try:
            return list(topological_sort(numCourses, prerequisites))
        except Exception:
            return []


def topological_sort(num_vertices, edges):
    vertices = [set() for _ in range(num_vertices)]
    for course, dependency in edges:
        vertices[course].add(dependency)

    output = set()

    def visit(i, ancestors):
        if i in output:
            return
        elif i in ancestors:
            raise Exception('cycle')
        else:
            ancestors.add(i)
            for j in vertices[i]:
                yield from visit(j, ancestors)
            output.add(i)
            yield i
            

    for i in range(num_vertices):
        yield from visit(i, set())
