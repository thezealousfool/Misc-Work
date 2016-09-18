#include <iostream>
#include <vector>
#include <algorithm>


// zero indexed priority queue using vector

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
void push_up_heap (std::vector<VALUE>& heap, std::size_t index) {

    while (parent(index) >= 0 && parent(index) < heap.size() && heap[parent(index)] > heap[index]) {
        VALUE temp;
        temp = heap[parent(index)];
        heap[parent(index)] = heap[index];
        heap[index] = temp;
        index = parent(index);
    }
}

template <typename VALUE>
void push_down_heap (std::vector<VALUE>& heap, std::size_t index, std::size_t ignore_elements = 0) {

    std::size_t focus;

    while (index < heap.size() - ignore_elements) {
        focus = index;
        if (left_child(index) < (heap.size() - ignore_elements) && heap[left_child(index)] < heap[focus])
            focus = left_child(index);
        if (right_child(index) < (heap.size() - ignore_elements) && heap[right_child(index)] < heap[focus])
            focus = right_child(index);
        if (focus == index)
            break;
        VALUE temp;
        temp = heap[focus];
        heap[focus] = heap[index];
        heap[index] = temp;
        index = focus;
    }
}

template <typename VALUE>
void decrease_key (std::vector<VALUE>& heap, std::size_t index, VALUE value) {

    if (value >= heap[index])
        return;

    heap[index] = value;
    push_up_heap (heap, index);
}

template <typename VALUE>
void increase_key (std::vector<VALUE>& heap, std::size_t index, VALUE value) {

    if (value <= heap[index])
        return;

    heap[index] = value;
    push_down_heap (heap, index);
}

template <typename VALUE>
void pop_binary_heap (std::vector<VALUE>& heap) {

    if (heap.size() <= 0)
        return;

    VALUE temp;
    temp = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap[heap.size() - 1] = temp;

    push_down_heap (heap, 0, 1);
}

template <typename VALUE>
void make_binary_heap (std::vector<VALUE>& heap) {

    for (std::size_t i = 1; i < heap.size(); ++i) {
        push_up_heap (heap, i);
    }
}

int main() {
    std::vector<double> pq = {20.2,5.5,7.3,1.3,3.7,6.8,9.1,22.5,11.4,10.9,27.3,4.0};
    make_binary_heap (pq);
    std::for_each (pq.cbegin(), pq.cend(), [](const double& i){ std::cout << i << " "; }); std::cout << std::endl;
    decrease_key (pq, 1, 3.1);
    increase_key (pq, 4, 5.7);
    while (pq.size() > 0) {
        pop_binary_heap(pq);
        std::cout << pq.back() << " ";
        pq.pop_back();
    }
    return 0;
}