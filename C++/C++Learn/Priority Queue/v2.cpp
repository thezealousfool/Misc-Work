#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <string>

template <typename RandomAccessIterator, typename Compare>
void push_binary_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    typedef typename std::iterator_traits<RandomAccessIterator>::difference_type index;
    typedef typename std::iterator_traits<RandomAccessIterator>::value_type value;
    index element_index = last - first;
    index parent = (element_index - 1) / 2;
    while (parent >= first && comp(*element_index, *parent)) {
        value temp = *parent;
        *parent = *element_index;
        *element_index = temp;
        element_index = parent;
        parent = (element_index - 1) / 2;
    }
}


int main() {
    std::vector<int> pq = {1};
    // std::map<string, int> map;
    // map["Node 1"] = 0;
    push_binary_heap(pq.begin(), pq.end(), [](const int& i1, const int& i2){ return i2 < i1; });
    return 0;
}