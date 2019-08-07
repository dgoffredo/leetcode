import re


# leetcode.com boilerplate
class Solution:
    def calculate(self, s: str) -> int:
        tokens = lex(s)
        polish = parse(tokens)
        return evaluate(reversed(polish))


def lex(expression):
    return re.findall(r'\(|\)|\+|-|[0-9]+', expression)


def parse(tokens):
    args = []
    ops = []
    depth = 0
    for token in tokens:
        try:
            token = int(token)
        except ValueError:
            pass

        if token == '(':
            depth += 1
            ops.append(token)
        elif token != ')':
            if type(token) is int:
                args.append(token)
            else:
                ops.append(token)
        else:
            while True:
                op = ops.pop()
                if op == '(':
                    depth -= 1
                    break

                b, a = args.pop(), args.pop()
                result = [op, a, b]
                args.append(result)

    # process any remaining operations
    while ops:
        op = ops.pop()
        b, a = args.pop(), args.pop()
        result = [op, a, b]
        args.append(result)

    print(args[0])
    return list(walk(args[0]))


def walk(obj):
    if type(obj) is not list:
        yield obj
        return

    for item in obj:
        yield from walk(item)


def evaluate(instructions):
    stack = []
    for instruction in instructions:
        if instruction == '+':
            b, a = stack.pop(), stack.pop()
            stack.append(a + b)
        elif instruction == '-':
            b, a = stack.pop(), stack.pop()
            stack.append(a - b)
        else:
            stack.append(instruction)

    return stack[0]
