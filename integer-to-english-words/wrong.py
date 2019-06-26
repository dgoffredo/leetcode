
class Solution:
    def numberToWords(self, num: int) -> str:
        return int_to_english(num)


def int_to_english(integer):
    if integer == 0:
        return 'Zero'

    ones = ['', 'One', 'Two', 'Three', 'Four', 'Five', 'Six', 'Seven', 'Eight',
            'Nine']
    teens = ['Ten', 'Eleven', 'Twelve', 'Thirteen', 'Fourteen', 'Fifteen',
             'Sixteen', 'Seventeen', 'Eighteen', 'Nineteen']
    tens = ['', '', 'Twenty', 'Thirty', 'Forty', 'Fifty', 'Sixty', 'Seventy',
            'Eighty', 'Ninety']

    # this list will have the words in reverse order
    words = []

    one = integer % 10
    integer //= 10
    ten = integer % 10
    # special case for teens, otherwise it's regular
    if ten == 1:
        words.append(teens[one])
    else:
        words.append(ones[one])
        words.append(tens[ten])

    def next_place(integer, name):
        integer //= 10
        value = integer % 10
        if value:
            words.append(name)
            words.append(ones[value])
        return integer

    integer = next_place(integer, 'Hundred')
    integer = next_place(integer, 'Thousand')
    integer = next_place(integer, 'Million')
    integer = next_place(integer, 'Billion')

    # Result is space-separated words in the correct order, but skipping the
    # empty ones.
    return ' '.join(word for word in reversed(words) if word)
