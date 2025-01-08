class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def in_order(node):
    if node.left is not None:
        yield from in_order(node.left)
    yield node.val
    if node.right is not None:
        yield from in_order(node.right)

class BSTIterator:

    def __init__(self, root: Optional[TreeNode]):
        self.generator = in_order(root)
        self.val = None
        self.done = False
        self.advance()

    def advance(self):
        try:
            self.val = next(self.generator)
        except StopIteration:
            self.done = True

    def next(self) -> int:
        result = self.val
        self.advance()
        return result

    def hasNext(self) -> bool:
        return not self.done


# Your BSTIterator object will be instantiated and called as such:
# obj = BSTIterator(root)
# param_1 = obj.next()
# param_2 = obj.hasNext()
