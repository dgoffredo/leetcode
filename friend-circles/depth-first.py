
from typing import List

class Solution:
    def findCircleNum(self, M: List[List[int]]) -> int:
        return num_connected_components(M)


def num_connected_components(adjacency_matrix):
    friendships = adjacency_matrix
    kid_clique = [None for _ in friendships] # kid index -> (None | clique #)
    latest_clique = 0 # incremented each time another is found

    def visit(kid, seen, clique=None):
        if kid in seen:
            return

        seen.add(kid)

        for classmate in range(kid, len(friendships)):
            if friendships[kid][classmate] == 0:
                continue

            friend = classmate
            friend_clique = kid_clique[friend]
            if friend_clique is not None:
                if clique is not None:
                    if friend_clique != clique:
                        raise Exception(f'We are kid {kid}.  Current clique is {clique} but friend {friend} has clique {friend_clique}')
                else:
                    # We found a friend who has a clique, so that's now ours.
                    for buddy in seen:
                        kid_clique[buddy] = friend_clique

                    clique = friend_clique
            elif clique is not None:
                kid_clique[friend] = clique

            # Otherwise, we need to check out this friend's friends as well.
            visit(friend, seen, clique)

    for kid in range(len(friendships)):
        if kid_clique[kid] is not None:
            # TODO: This might be the issue.  The kid was previously marked as
            #       part of a clique, but we didn't continue to mark _his_
            #       friends (who we hadn't seen before).
            # TODO: Actually, I might have just fixed it above, in `visit`.
            continue

        seen = set()
        visit(kid, seen)

        if kid_clique[kid] is None:
            # We didn't find a clique to be part of, so that means we're a new
            # clique, _unless_ we are alone and not even our own friends.
            if len(seen) == 1 and friendships[kid][kid] == 0:
                continue # NO FRIENDS

            latest_clique += 1
            for friend in seen:
                kid_clique[friend] = latest_clique

    return latest_clique
