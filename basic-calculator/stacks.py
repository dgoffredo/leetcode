import re


# leetcode.com boilerplate
class Solution:
    def calculate(self, s: str) -> int:
        tokens = lex(s)
        polish = parse(tokens)
        print('parsed:', polish)
        return evaluate(reversed(polish))


def lex(expression):
    return re.findall(r'\(|\)|\+|-|[0-9]+', expression)


def parse(tokens):
    args = []
    ops = []

    def process_op(op):
        print(op, 'just popped from', ops, 'and args are', args)
        b, a = args.pop(), args.pop()
        result = [op, a, b]
        args.append(result)

    for token in tokens:
        try:
            token = int(token)
        except ValueError:
            pass

        if token == ')':
            while True:
                op = ops.pop()
                if op == '(':
                    break
                process_op(op)
        elif token == '(':
            ops.append(token)
        else:
            if type(token) is int:
                args.append(token)
            else:
                ops.append(token)

            if len(args) > 1 and ops and ops[-1] != '(':
                process_op(ops.pop())

    # process any remaining operations
    while ops:
        process_op(ops.pop())

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
            a, b = stack.pop(), stack.pop()
            stack.append(a + b)
        elif instruction == '-':
            a, b = stack.pop(), stack.pop()
            stack.append(a - b)
        else:
            stack.append(instruction)
        print(stack)

    return stack[0]
