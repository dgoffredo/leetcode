
class Solution:
    def intToRoman(self, num: int) -> str:
        return int_to_roman_numeral(num)


def roman_place(low, middle, high):
    return [
        '',
        low, low * 2, low * 3,
        low + middle,
        middle, middle + low, middle + low * 2, middle + low * 3,
        low + high
    ]


def int_to_roman_numeral(integer):
    thousands = ['M' * i for i in range(10)]
    hundreds = roman_place('C', 'D', 'M')
    tens = roman_place('X', 'L', 'C')
    ones = roman_place('I', 'V', 'X')

    one = integer % 10
    integer //= 10
    ten = integer % 10
    integer //= 10
    hundred = integer % 10
    integer //= 10
    thousand = integer % 10

    return thousands[thousand] + hundreds[hundred] + tens[ten] + ones[one]
