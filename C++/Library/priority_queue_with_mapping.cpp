#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>


// zero indexed priority queue using vector
// mapping and reverse mapping are two vector<std::size_t>

constexpr inline std::size_t left_child (std::size_t index) {

    return (2 * index) + 1;
}

constexpr inline std::size_t right_child (std::size_t index) {

    return (2 * index) + 2;
}

constexpr inline std::size_t parent (std::size_t i) {

    if (i<0)
        return -1;
    return (i - 1) / 2;
}

template <typename VALUE>
void push_up_heap (std::vector<VALUE>& heap, std::size_t index, std::vector<std::size_t>& mapping, std::vector<std::size_t>& reverse_mapping) {

    while (parent(index) >= 0 && parent(index) < heap.size() && heap[parent(index)] > heap[index]) {

        mapping[reverse_mapping[index]] = parent(index);
        mapping[reverse_mapping[parent(index)]] = index;
        std::size_t temp_index = reverse_mapping[index];
        reverse_mapping[index] = reverse_mapping[parent(index)];
        reverse_mapping[parent(index)] = temp_index;

        VALUE temp;
        temp = heap[parent(index)];
        heap[parent(index)] = heap[index];
        heap[index] = temp;
        index = parent(index);
    }
}

template <typename VALUE>
void push_down_heap (std::vector<VALUE>& heap, std::size_t index, std::vector<std::size_t>& mapping, std::vector<std::size_t>& reverse_mapping, std::size_t ignore_elements = 0) {

    std::size_t focus;

    while (index < heap.size() - ignore_elements) {

        focus = index;
        if (left_child(index) < (heap.size() - ignore_elements) && heap[left_child(index)] < heap[focus])
            focus = left_child(index);
        if (right_child(index) < (heap.size() - ignore_elements) && heap[right_child(index)] < heap[focus])
            focus = right_child(index);
        if (focus == index)
            break;

        mapping[reverse_mapping[focus]] = index;
        mapping[reverse_mapping[index]] = focus;
        std::size_t temp_index = reverse_mapping[focus];
        reverse_mapping[focus] = reverse_mapping[index];
        reverse_mapping[index] = temp_index;

        VALUE temp;
        temp = heap[focus];
        heap[focus] = heap[index];
        heap[index] = temp;
        index = focus;
    }
}

template <typename VALUE>
void decrease_key (std::vector<VALUE>& heap, std::size_t index, VALUE value, std::vector<std::size_t>& mapping, std::vector<std::size_t>& reverse_mapping) {

    if (mapping[index] >= heap.size())
        return;

    if (value >= heap[mapping[index]])
        return;

    heap[mapping[index]] = value;
    push_up_heap (heap, mapping[index], mapping, reverse_mapping);
}

template <typename VALUE>
void increase_key (std::vector<VALUE>& heap, std::size_t index, VALUE value, std::vector<std::size_t>& mapping, std::vector<std::size_t>& reverse_mapping) {

    if (mapping[index] >= heap.size())
        return;

    if (value <= heap[mapping[index]])
        return;

    heap[mapping[index]] = value;
    push_down_heap (heap, mapping[index], mapping, reverse_mapping);
}

template <typename VALUE>
void pop_binary_heap (std::vector<VALUE>& heap, std::vector<std::size_t>& mapping, std::vector<std::size_t>& reverse_mapping) {

    if (heap.size() <= 0)
        return;

    std::size_t temp_index = reverse_mapping[0];
    reverse_mapping[0] = reverse_mapping[heap.size() - 1];
    reverse_mapping[mapping.size() - 1] = temp_index;
    mapping[reverse_mapping[0]] = 0;
    mapping[reverse_mapping[mapping.size() - 1]] = -1;
    reverse_mapping[heap.size() - 1] = -1;

    VALUE temp;
    temp = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap[heap.size() - 1] = temp;

    push_down_heap (heap, 0, mapping, reverse_mapping, 1);
}

template <typename VALUE>
void make_binary_heap (std::vector<VALUE>& heap, std::vector<std::size_t>& mapping, std::vector<std::size_t>& reverse_mapping) {

    for (std::size_t i = 1; i < heap.size(); ++i) {
        push_up_heap (heap, i, mapping, reverse_mapping);
    }
}

int main() {
    auto fin = std::fstream("input.txt", std::ios::in);
    auto fout = std::fstream("output.txt", std::ios::out);
    int n = 40100;
    std::vector<int> pq(n);
    std::vector<std::size_t> mapping (pq.size());
    std::vector<std::size_t> reverse_mapping (pq.size());
    for (auto i = 0; i < n; ++i)
	    fin >> pq[i];
    for (int i=0; i<pq.size(); ++i) {
        mapping[i] = reverse_mapping[i] = i;
    }
    auto start = std::chrono::steady_clock::now();
    make_binary_heap (pq, mapping, reverse_mapping);

    decrease_key (pq, 1, 4, mapping, reverse_mapping);
    increase_key (pq, 0, 8, mapping, reverse_mapping);
    while (pq.size() > 0) {
        pop_binary_heap(pq, mapping, reverse_mapping);
        fout << pq.back() << "\n";
        pq.pop_back();
    }
    auto end = std::chrono::steady_clock::now();
    auto time = end - start;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "\n";
    return 0;
}
