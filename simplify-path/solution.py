
# leetcode.com boilerplate
class Solution:
    def simplifyPath(self, path: str) -> str:
        return simplify_path(path)


def simplify_path(path):
    pieces = split_path(path)
    canonical = []

    for piece in pieces:
        if piece == '.':
            continue
        elif piece == '..':
            # This corner case isn't mentioned in the problem description, but
            # appears in one of the test cases.
            if len(canonical) != 0:
                canonical.pop()
        else:
            canonical.append(piece)

    return '/' + '/'.join(canonical)


def split_path(path):
    pieces = path.split('/')
    return [piece for piece in pieces if piece != '']
        