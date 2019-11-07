import re
from typing import List


class Solution:
    def spellchecker(self, wordlist: List[str], queries: List[str]) -> List[str]:
        return fuzzy_lookup(wordlist, queries)


def devowel(word):
    return re.sub('[aeiouAEIOU]', '0', word)


def fuzzy_lookup(words, queries):
    words_set = set(words)

    words_lower = {} # lower cased -> index in words
    for i, word in enumerate(words):
        lower = word.lower()
        if lower not in words_lower:
            words_lower[lower] = i


    words_devoweled = {} # vowels replaced with '0' -> index in words
    for i, word in enumerate(words):
        devoweled = devowel(word.lower())
        if devoweled not in words_devoweled:
            words_devoweled[devoweled] = i


    result = []
    for query in queries:
        if query in words_set:
            result.append(query)
            continue

        entry = words_lower.get(query.lower())
        if entry is not None:
            result.append(words[entry])
            continue

        entry = words_devoweled.get(devowel(query.lower()))
        if entry is not None:
            result.append(words[entry])
            continue

        result.append('')

    return result
