#include <iostream>
#include <vector>
#include <map>
#include <functional>


// zero indexed
template <typename Container, typename Mapping = std::map<std::size_t, std::size_t>>
class priority_queue {

    public:

    Container container;
    std::size_t no_of_elements;
    Mapping indexing;
    std::map<typename Mapping::mapped_type, typename Mapping::key_type> reverse_indexing;
    std::function<bool (typename Container::value_type, typename Container::value_type)> comp;

    constexpr inline std::size_t parent (std::size_t i) {
        return (i - 1) / 2;
    }

    constexpr inline std::size_t left_child (std::size_t i) {
        return (2 * i) + 1;
    }

    constexpr inline std::size_t right_child (std::size_t i) {
        return (2 * i) + 2;
    }    

    void push_heap (std::size_t index) {
        while (parent(index) >= 0 && comp(container[index], container[parent(index)])) {
            indexing[reverse_indexing[index]] = parent(index);
            indexing[reverse_indexing[parent(index)]] = index;
            auto temp2 = reverse_indexing[index];
            reverse_indexing[index] = reverse_indexing[parent(index)];
            reverse_indexing[parent(index)] = temp2;
            typename Container::value_type temp = container[index];
            container[index] = container[parent(index)];
            container[parent(index)] = temp;
            index = parent(index);
        }
    }

    typename Mapping::key_type pop_heap () {
        if (no_of_elements <= 0)
            return -1;
        typename Container::value_type temp = container[0];
        typename Mapping::key_type return_val = reverse_indexing[0];
        indexing.erase (reverse_indexing[0]);
        container[0] = container[no_of_elements - 1];
        indexing[reverse_indexing[no_of_elements - 1]] = 0;
        reverse_indexing[0] = reverse_indexing[no_of_elements - 1];
        container[no_of_elements - 1] = temp;
        reverse_indexing.erase(no_of_elements - 1);
        --no_of_elements;
        std::size_t index = 0, focus = index;
        while (index < no_of_elements) {
            focus = index;
            if ((left_child(index) < no_of_elements) && comp(container[left_child(index)], container[focus]))
                focus = left_child(index);
            if ((right_child(index) < no_of_elements) && comp(container[right_child(index)], container[focus]))
                focus = right_child(index);
            if (focus == index)
                break;
            indexing[reverse_indexing[focus]] = index;
            indexing[reverse_indexing[index]] = focus;
            auto temp2 = reverse_indexing[focus];
            reverse_indexing[focus] = reverse_indexing[index];
            reverse_indexing[index] = temp2;
            temp = container[focus];
            container[focus] = container[index];
            container[index] = temp;
            index = focus;
        }
        return return_val;
    }

    void update_key (std::size_t index, typename Container::value_type new_value) {
        container[indexing[index]] = new_value;
        push_heap (indexing[index]);
    }

    priority_queue () : container(Container()), no_of_elements(0), comp([](typename Container::value_type elem1, typename Container::value_type elem2){return elem2 < elem1;}) { }

    priority_queue (const Container& c) : container(c), no_of_elements(c.size()), comp([](typename Container::value_type elem1, typename Container::value_type elem2){return elem2 < elem1;}) {
        for (size_t i = 0; i < no_of_elements; ++i) {
            indexing[i] = i;
            reverse_indexing[i] = i;
        }
        for (size_t i = 0; i < no_of_elements; ++i)
            push_heap (i);
    }

    priority_queue (const Container& c, const Mapping& m, const decltype(reverse_indexing)& r_m) : container(c), no_of_elements(c.size()), indexing(m), reverse_indexing(r_m), comp([](typename Container::value_type elem1, typename Container::value_type elem2){return elem2 < elem1;}) {
        for (size_t i = 0; i < no_of_elements; ++i)
            push_heap (i);
    }

    priority_queue (const Container& c, const std::function<bool (typename Container::value_type, typename Container::value_type)>& cmp) : container(c), no_of_elements(c.size()), comp(cmp) {
        for (size_t i = 0; i < no_of_elements; ++i) {
            indexing[i] = i;
            reverse_indexing[i] = i;
        }
        for (size_t i = 0; i < no_of_elements; ++i)
            push_heap (i);
    }

    priority_queue (const Container& c, const std::function<bool (typename Container::value_type, typename Container::value_type)>& cmp, const Mapping& m, const decltype(reverse_indexing)& r_m) : container(c), no_of_elements(c.size()), indexing(m), reverse_indexing(r_m), comp(cmp) {
        for (size_t i = 0; i < no_of_elements; ++i)
            push_heap (i);
    }

};

int main() {
    std::vector<int> v = {3,2,1,4,5};
    priority_queue<std::vector<int>> pq(v);
    while (pq.container.size()>0) {
        std::size_t index = pq.pop_heap();
        std::cout << "Index " << index << ": " << pq.container.back() << "\n" ;
        pq.container.pop_back();
    }
    return 0;
}