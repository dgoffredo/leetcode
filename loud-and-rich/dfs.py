
from typing import List


class Solution:
    def loudAndRich(self, richer: List[List[int]], quiet: List[int]) -> List[int]:
        return loud_and_rich(richer, quiet)


def loud_and_rich(richer_than, quietness):
    num_people = len(quietness)

    # graph repr := {vertex: set(edges)}, but as list with index = vertex.
    poorer_than = [set() for _ in range(num_people)]
    
    for rich, poor in richer_than:
        poorer_than[poor].add(rich)

    # Now we have a graph (poorer_than) that we can traverse depth-first,
    # collecting information about the "quietest" from the leaves up to each
    # other node.

    answer = [None] * num_people

    def visit(person):
        if answer[person] is not None:
            return answer[person]

        richers = poorer_than[person]
        
        if len(richers) == 0:
            # We're locally rich, so the quietest person whose wealth is
            # greater than or equal to ours is... us.
            answer[person] = person
            return person

        # If there are people richer than us, then we take the quietest among
        # them and us.
        louders = set(visit(neighbor) for neighbor in richers)
        louders.add(person)
        
        loudest = min((quietness[index], index) for index in louders)[1]
        answer[person] = loudest
        return loudest

    for i in range(num_people):
        if answer[i] is None:
            visit(i)

    return answer
