import re


# leetcode.com boilerplate
class Solution:
    def calculate(self, s: str) -> int:
        tokens = lex(s)
        reverse_polish = parse(tokens)
        # print('parsed:', reverse_polish)
        return evaluate(reverse_polish)


def lex(expression):
    return re.findall(r'\(|\)|\+|-|[0-9]+', expression)


def maybe_parse_int(token):
    try:
        token = int(token)
    except ValueError:
        pass

    return token


def parse(tokens):
    ops = [] # a stack
    result = [] # a list

    def process_ops():
        while ops and ops[-1] != '(':
            result.append(ops.pop())

    for token in tokens:
        token = maybe_parse_int(token)

        # two cases:
        #   - int -> push onto result.  If ops nonempty and last not "(", pop.
        #   - str -> if not ")", push onto ops.  If ")", then assert ops ends
        #            with "(".  Pop it and pop until next "(" or until empty.
        if type(token) is int:
            result.append(token)
            process_ops()
        else:
            if token != ')':
                ops.append(token)
            else:
                assert ops
                assert ops[-1] == '('
                ops.pop()
                process_ops()

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
        else:
            stack.append(instruction)

        # print(f'after instruction {instruction}: {stack}')

    return stack[0]
