
#include <algorithm>
#include <cassert>
#include <iostream>  // debugging
#include <iterator>
#include <numeric>
#include <ostream>
#include <vector>

double medianOfMerger(const std::vector<int>&, const std::vector<int>&);

// std::ostream debug(0);
std::ostream debug(std::cout.rdbuf());

// leetcode.com boilerplate
class Solution {
public:
    double findMedianSortedArrays(const std::vector<int>& left,
                                  const std::vector<int>& right)
    {
        debug << "left: ";
        std::copy(left.begin(), left.end(), std::ostream_iterator<int>(debug, " "));
        debug << "\nright: ";
        std::copy(right.begin(), right.end(), std::ostream_iterator<int>(debug, " "));
        debug << "\n";

        return medianOfMerger(left, right);
    }
};


// implementation
int findValueWithRank(const std::vector<int>& left,
                      const std::vector<int>& right,
                      int                     rank);

double median(const std::vector<int>& values);

double medianOfMerger(const std::vector<int>& left,
                      const std::vector<int>& right)
{
    // The idea is to simultaneously binary search through both vectors looking
    // for the median value(s). We know the rank of a value within the merged
    // sequence by adding together the value's rank in 'left' and its rank in
    // 'right'.
    //
    // If 'left.size() + right.size()' is odd, then there's only one rank
    // (value) to search for. If that sum is even, then there are two ranks to
    // look for.
    //
    // The algorithm begins by picking one of the vectors arbitrarily (say,
    // 'left'), and does a binary search for the value having the desired rank.
    // At each step of the binary search, the value is looked up in the other
    // vector as well (using 'std::lower_bound' on a narrowing range). From 
    // this, the rank of the "current value" in the merged sequence can be
    // determined. If it's what we're looking for, then we're done. If the rank
    // is too high, then we proceed with the search one way, and if the rank is
    // too small, then we proceed with the search the other way. Finally if
    // there is no more searching to be done, then the algorithm starts again,
    // but this time starting with the other vector (e.g. 'right').
    //
    // The above is performed for each of the one or two ranks sought,
    // depending on whether 'left.size() + right.size()' is even or odd. Then
    // either the rank is returned (odd case) or the average of the two ranks
    // is returned (even case).
    //
    // Rank is considered to be zero-based.

    // Corner case: either of 'left' or 'right' is empty.
    if (left.empty()) {
        return median(right);
    }

    if (right.empty()) {
        return median(left);
    }

    const int        mergedLength = left.size() + right.size();
    std::vector<int> ranks;

    ranks.push_back(mergedLength / 2);
    if (mergedLength % 2 == 0) {
        ranks.push_back(mergedLength / 2 - 1);
    }

    std::vector<int> values;
    for (int rank : ranks) {
        values.push_back(findValueWithRank(left, right, rank));
    }

    const int sum = std::accumulate(values.begin(), values.end(), 0);
    return sum / double(values.size());
}

int findValueWithRank(const std::vector<int>& left,
                      const std::vector<int>& right,
                      int                     rank)
{
    debug << "looking for rank " << rank << "\n";

    assert(rank >= 0);
    assert(rank < int(left.size() + right.size()));

    // We always assume to be looking for the value in 'left'. If it's not
    // found in 'left', then we just return the result of calling ourselves
    // with 'left' and 'right' interchanged. Due to the assertions above, and
    // to the assumption that 'left' and 'right' are each sorted, we're
    // guaranteed to find it in one or the other.

    typedef std::vector<int>::const_iterator Iter;
    
    Iter leftIter = left.begin();
    Iter leftHigh = left.end();
    Iter leftLow  = left.begin();
    Iter rightIter = right.begin();  // initial value is not relevant
    Iter rightHigh = right.end();
    Iter rightLow  = right.begin();

    for (;;) {
        debug << "i = " << std::distance(left.begin(), leftIter)
                  << "    "
                  << "j = " << std::distance(right.begin(), rightIter)
                  << "\n";
        assert(leftIter != left.end());

        rightIter = std::lower_bound(rightLow, rightHigh, *leftIter);
        const int beginRanks = std::distance(left.begin(), leftIter) +
                               std::distance(right.begin(), rightIter);
        const int numCopies =
            std::distance(leftIter,
                          std::upper_bound(leftIter, left.end(), *leftIter)) +
            std::distance(rightIter,
                          std::upper_bound(rightIter, right.end(), *leftIter));
        const int endRanks = beginRanks + numCopies;

        if (rank >= beginRanks && rank < endRanks) {
            debug << "found rank " << rank << "\n";
            return *leftIter;
        }
        else if (beginRanks > rank) {
            const Iter leftNext = leftLow +
                                  std::distance(leftLow, leftIter) / 2;
            debug << "rank " << beginRanks << " is larger than " << rank << "\n";
            if (leftNext == leftIter) {
                // Nowhere left to search. Try the other way around;
                return findValueWithRank(right, left, rank);
            }
            
            leftHigh = leftIter;
            leftIter = leftNext;
            // TODO: narrow the range of 'right', too.
        }
        else {
            assert(endRanks <= rank);
            debug << "rank " << beginRanks << " is smaller than " << rank << "\n";
            const Iter leftNext = leftIter +
                                  std::distance(leftIter, leftHigh) / 2;
            if (leftNext == leftIter) {
                // Nowhere left to search. Try the other way around.
                return findValueWithRank(right, left, rank);
            }

            leftLow  = leftIter;
            leftIter = leftNext;
            // TODO: narrow the range of 'right', too.
        }
    }
}

double median(const std::vector<int>& values)
{
    assert(!values.empty());

    const int halfway = values.size() / 2;

    if (values.size() % 2 == 0) {
        return (values[halfway] + values[halfway - 1]) / 2.0;
    }
    else {
        return values[halfway];
    }
}
