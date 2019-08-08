import math
import re


# leetcode.com boilerplate
class Solution:
    def calculate(self, s: str) -> int:
        tokens = lex(s)
        reverse_polish = parse(tokens)
        # print('parsed:', reverse_polish)
        return evaluate(reverse_polish)


def lex(expression):
    return re.findall(r'\+|-|\*|/|[0-9]+', expression)


def maybe_parse_int(token):
    try:
        token = int(token)
    except ValueError:
        pass

    return token


def precedence(operator):
    return {
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2
    }[operator]


def parse(tokens):
    ops = [] # a stack
    result = [] # a list

    for token in tokens:
        token = maybe_parse_int(token)

        # Two cases:
        #   - int? push it onto the result
        #   - str? while ops is nonempty and there's a >= precedence op on top,
        #          pop that op.  Then push (this) op onto ops
        # Then at the end, pop any remaining ops.
        if type(token) is int:
            result.append(token)
        else:
            while ops and precedence(ops[-1]) >= precedence(token):
                result.append(ops.pop())
            ops.append(token)

    while ops:
        result.append(ops.pop())

    assert len(ops) == 0
    return result


def evaluate(instructions):
    stack = []
    for instruction in instructions:
        if instruction == '+':
            b, a = stack.pop(), stack.pop()
            stack.append(a + b)
        elif instruction == '-':
            b, a = stack.pop(), stack.pop()
            stack.append(a - b)
        elif instruction == '*':
            b, a = stack.pop(), stack.pop()
            stack.append(a * b)
        elif instruction == '/':
            b, a = stack.pop(), stack.pop()
            stack.append(math.trunc(a / b))
        else:
            stack.append(instruction)

        # print(f'after instruction {instruction}: {stack}')

    return stack[0]
