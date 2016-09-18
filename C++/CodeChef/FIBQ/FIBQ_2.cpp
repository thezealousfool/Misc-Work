#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>

constexpr std::int64_t Mod = (int)1E9 + 7;

std::vector<int> fib_store(101, -1);

int fib (int index) {

    if (index <= 0) {
        return 0;
    }
    if (index <= 2) {
        return 1;
    }
    if (index == 3) {
        return 2;
    }
    if (index <= 100 && fib_store[index] != -1) {
        return fib_store[index];
    }

    return fib_store[index] = (((fib(std::floor(index/2.0))*fib(std::ceil(index/2.0)+1))%Mod) + ((fib(std::floor(index/2.0)-1)*fib(std::ceil(index/2.0)))%Mod))%Mod;
}

void populate_segtree (std::vector<std::int64_t>& array, std::vector<std::int64_t>& segtree_fib_minus_one, std::vector<std::int64_t>& segtree_fib, std::vector<std::int64_t>& segtree_fib_plus_one, std::vector<std::int64_t>& start, std::vector<std::int64_t>& end, int index) {

    if (start[index] == end[index] || (2*index + 1 >= segtree_fib.size())) {
        segtree_fib[index] = fib(array[start[index]]);
        segtree_fib_minus_one[index] = fib(array[start[index]] - 1);
        segtree_fib_plus_one[index] = fib(array[start[index]] + 1);
        if ((2*index + 2) < segtree_fib.size()) {
            start[2*index + 1] = end[2*index + 1] = start[2*index + 2] = end[2*index + 2] = start[index];
            segtree_fib[2*index + 1] = segtree_fib[2*index + 2] = segtree_fib[index];
            segtree_fib_minus_one[2*index + 1] = segtree_fib_minus_one[2*index + 2] = segtree_fib_minus_one[index];
            segtree_fib_plus_one[2*index + 1] = segtree_fib_plus_one[2*index + 2] = segtree_fib_plus_one[index];
        }

        return;        
    }

    start [2*index + 1] = start[index];
    end[2*index + 2] = end[index];
    end[2*index + 1] = (end[index] - start[index]) / 2 + start[index];
    start[2*index + 2] = std::min(end[2*index + 1] + 1, end[2*index + 2]);

    populate_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, 2*index + 1);
    populate_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, 2*index + 2);

    segtree_fib[index] = (segtree_fib[2*index + 1] + segtree_fib[2*index + 2] + segtree_fib[2*index + 1]*segtree_fib_plus_one[2*index + 2] + segtree_fib_minus_one[2*index + 1]*segtree_fib[2*index + 2]) % Mod;
    segtree_fib_plus_one[index] = (segtree_fib_plus_one[2*index + 1] + segtree_fib_plus_one[2*index + 2] + segtree_fib_plus_one[2*index + 1]*segtree_fib_plus_one[2*index + 2] + segtree_fib[2*index + 1]*segtree_fib[2*index + 2]) % Mod;
    segtree_fib_minus_one[index] = (segtree_fib_minus_one[2*index + 1] + segtree_fib_minus_one[2*index + 2] + segtree_fib[2*index + 1]*segtree_fib[2*index + 2] + segtree_fib_minus_one[2*index + 1]*segtree_fib_minus_one[2*index + 2]) % Mod;
}

std::tuple<int64_t, int64_t, int64_t> query_segtree (std::vector<std::int64_t>& segtree_fib_minus_one, std::vector<std::int64_t>& segtree_fib, std::vector<std::int64_t>& segtree_fib_plus_one, std::vector<std::int64_t>& start, std::vector<std::int64_t>& end,  int start_index, int end_index, int present_node_index) {
    if (start[present_node_index] >= start_index && end[present_node_index] <= end_index) {
        return std::make_tuple(segtree_fib_minus_one[present_node_index], segtree_fib[present_node_index], segtree_fib_plus_one[present_node_index]);
    }
    if (start[present_node_index] > end_index || end[present_node_index] < start_index) {
        return std::make_tuple(0,0,0);
    }

    auto left_child = query_segtree(segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, start_index, end_index, 2*present_node_index + 1);
    auto right_child = query_segtree(segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, start_index, end_index, 2*present_node_index + 2);

    if (std::get<1>(left_child) == 0)
        return right_child;
    if (std::get<1>(right_child) == 0)
        return left_child;

    auto A_minus_one = std::get<0>(left_child);
    auto A = std::get<1>(left_child);
    auto A_plus_one = std::get<2>(left_child);

    auto B_minus_one = std::get<0>(right_child);
    auto B = std::get<1>(right_child);
    auto B_plus_one = std::get<2>(right_child);

    return std::make_tuple(A_minus_one + B_minus_one + A*B + A_minus_one*B_minus_one,
        A + B + A*B_plus_one + A_minus_one*B,
        A_plus_one + B_plus_one + A_plus_one*B_plus_one + A*B);
}

void update_segtree (std::vector<std::int64_t>& array, std::vector<std::int64_t>& segtree_fib_minus_one, std::vector<std::int64_t>& segtree_fib, std::vector<std::int64_t>& segtree_fib_plus_one, std::vector<std::int64_t>& start, std::vector<std::int64_t>& end, int update_index, int present_node_index) {

    if (update_index > end[present_node_index] || update_index < start[present_node_index]) {
        return;
    }

    if (end[present_node_index] == start[present_node_index] && start[present_node_index] == update_index) {
        segtree_fib[present_node_index] = fib(array[update_index]);
        segtree_fib_minus_one[present_node_index] = fib(array[update_index] - 1);
        segtree_fib_plus_one[present_node_index] = fib(array[update_index] + 1);
        if ((2*present_node_index + 2) < segtree_fib.size()) {
            segtree_fib[2*present_node_index + 1] = segtree_fib[2*present_node_index + 2] = segtree_fib[present_node_index];
            segtree_fib_minus_one[2*present_node_index + 1] = segtree_fib_minus_one[2*present_node_index + 2] = segtree_fib_minus_one[present_node_index];
            segtree_fib_plus_one[2*present_node_index + 1] = segtree_fib_plus_one[2*present_node_index + 2] = segtree_fib_plus_one[present_node_index];
        }
        return;
    }

    update_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, update_index, 2*present_node_index+1);
    update_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, update_index, 2*present_node_index+2);

    segtree_fib[present_node_index] = (segtree_fib[2*present_node_index + 1] + segtree_fib[2*present_node_index + 2] + segtree_fib[2*present_node_index + 1]*segtree_fib_plus_one[2*present_node_index + 2] + segtree_fib_minus_one[2*present_node_index + 1]*segtree_fib[2*present_node_index + 2]) % Mod;
    segtree_fib_plus_one[present_node_index] = (segtree_fib_plus_one[2*present_node_index + 1] + segtree_fib_plus_one[2*present_node_index + 2] + segtree_fib_plus_one[2*present_node_index + 1]*segtree_fib_plus_one[2*present_node_index + 2] + segtree_fib[2*present_node_index + 1]*segtree_fib[2*present_node_index + 2]) % Mod;
    segtree_fib_minus_one[present_node_index] = (segtree_fib_minus_one[2*present_node_index + 1] + segtree_fib_minus_one[2*present_node_index + 2] + segtree_fib[2*present_node_index + 1]*segtree_fib[2*present_node_index + 2] + segtree_fib_minus_one[2*present_node_index + 1]*segtree_fib_minus_one[2*present_node_index + 2]) % Mod;
}

int main() {

    std::ios::sync_with_stdio(false);

    int N, M, segtree_size;
    std::vector<std::int64_t> array((int)1E5);
    std::vector<std::int64_t> segtree_fib(132'000);
    std::vector<std::int64_t> segtree_fib_minus_one(132'000);
    std::vector<std::int64_t> segtree_fib_plus_one(132'000);
    std::vector<std::int64_t> start(132'000);
    std::vector<std::int64_t> end(132'000);

    std::cin >> N >> M;

    segtree_size = std::pow(2, std::ceil(std::log2(N)) + 1) - 1;

    array.resize(N);
    segtree_fib.resize(segtree_size);
    segtree_fib_plus_one.resize(segtree_size);
    segtree_fib_minus_one.resize(segtree_size);
    start.resize(segtree_size);
    end.resize(segtree_size);

    for (auto& elem : array)
        std::cin >> elem;

    start[0] = 0; end[0] = N-1;
    populate_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, 0);

    {
        char choice; int argument_one, argument_two;
        while (M--) {
            std::cin >> choice >> argument_one >> argument_two;
            if (choice == 'Q') {
                std::cout << std::get<1>(query_segtree(segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, argument_one - 1, argument_two - 1, 0)) << "\n";
            }
            else if (choice == 'C') {
                array[argument_one-1] = argument_two;
                update_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, argument_one-1, 0);
            }
        }
    }

    return 0;
}