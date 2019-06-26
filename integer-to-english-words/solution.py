
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

    integer //= 10
    hundred = integer % 10
    if hundred:
        words.append('Hundred')
        words.append(ones[hundred])

    integer //= 10

    for place in ['Thousand', 'Million', 'Billion']:
        value = integer % 1000
        count = int_to_english(value)
        if count != 'Zero':
            words.append(place)
            words.append(count)
        integer //= 1000

    # Result is space-separated words in the correct order, but skipping the
    # empty ones.
    return ' '.join(word for word in reversed(words) if word)
