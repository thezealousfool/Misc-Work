#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <functional>

template <typename WEIGHT>
struct edge {
	int vertex1, vertex2;
	WEIGHT weight;
};

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


template <typename T>
int prim_MST (const std::vector<edge<T>>& edges, int no_of_vertices) {

	int total_length = 0;

	std::vector<std::vector<std::pair <int, T>>> adjacency_list(no_of_vertices);

	for (const edge<T>& e : edges) {
		adjacency_list[e.vertex1].push_back(std::make_pair(e.vertex2, e.weight));
		adjacency_list[e.vertex2].push_back(std::make_pair(e.vertex1, e.weight));
	}

	std::vector<int> pqueue(no_of_vertices, std::numeric_limits<int>::max());
	std::vector<std::size_t> mapping(no_of_vertices);
	std::vector<std::size_t> reverse_mapping(no_of_vertices);

	for (int i=0; i<no_of_vertices; ++i) {
		mapping[i] = i;
		reverse_mapping[i] = i;
	}

	pqueue[0] = 0;
	int vertices_visited = 0, present_vertex;
	while (vertices_visited < no_of_vertices) {
		present_vertex = reverse_mapping[0];
		std::cout << present_vertex << "->";
		pop_binary_heap(pqueue, mapping, reverse_mapping);
		total_length += pqueue.back();
		pqueue.pop_back();
		for (auto& elem : adjacency_list[present_vertex]) {
			decrease_key(pqueue, elem.first, elem.second, mapping, reverse_mapping);
		}
		++vertices_visited;
	}

	std::cout << "end" << std::endl;

	return total_length;
}

int main() {

	std::vector<edge<int>> edges = { {0,1,4} , {7,0,8} , {1,7,11} , {7,8,7} , {7,6,1} , {1,2,8} , {6,8,6} , {8,2,2} , {6,5,2} , {2,5,4} , {2,3,7} , {3,5,14} , {3,4,9} , {5,4,10} };
	std::cout << prim_MST<int> (edges, 9) << std::endl;
	return 0;
}