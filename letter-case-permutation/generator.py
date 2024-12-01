
def case_combinations(text):
  # print('examining: ', text)
  if len(text) == 0:
    yield text
    return
  ch, rest = text[0], text[1:]
  if ord(ch) >= ord('0') and ord(ch) <= ord('9'):
    for suffix in case_combinations(rest):
      yield ch + suffix
    return
  for suffix in case_combinations(rest):
    yield ch.upper() + suffix
    yield ch.lower() + suffix


class Solution:
    def letterCasePermutation(self, s):
        return list(case_combinations(s))
