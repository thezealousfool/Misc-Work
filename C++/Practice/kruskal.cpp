#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

#define edge_t std::tuple<int, int, int>

std::vector<int> sets;

void init_set(int size) {
    sets.resize(size);
    for (int i = 0; i < size; ++i) {
        sets[i] = i;
    }
}

int parent(int n1) {
    if (n1 < 0 || n1 >= sets.size()) {
        std::cout << "invalid sets access: " << n1 << '\n';
        for (int i = 0; i < sets.size(); ++i) {
            std::cout << i << " - " << sets[i] << '\n';
        }
        exit(1);
    }
    return (n1 == sets[n1]) ? n1 : (sets[n1] = parent(sets[n1]));
}

void union_set(int n1, int n2) {
    sets[parent(n2)] = parent(n1);
}

int main(int argc, char const *argv[]) {
    int n_nodes;
    std::cout << "Enter no of nodes: ";
    std::cin >> n_nodes;
    init_set(n_nodes);
    std::vector<edge_t> edges;
    std::cout << "Enter edges:" << '\n';
    while (true) {
        int node1, node2, weight;
        if (!scanf("%d-%d %d", &node1, &node2, &weight))
            break;
        edges.push_back(std::make_tuple(node1, node2, weight));
    }
    std::sort(edges.begin(), edges.end(),
        [](const edge_t& e1,
            const edge_t& e2) {
            return std::get<2>(e1) < std::get<2>(e2);
        });
    std::vector<edge_t> mst;
    for (const edge_t& e : edges) {
        // check if adding e to the mst makes a loop
        if (parent(std::get<0>(e) - 1) != parent(std::get<1>(e) - 1)) {
            mst.push_back(e);
            union_set(std::get<0>(e) - 1, std::get<1>(e) - 1);
        }
    }
    std::sort(mst.begin(), mst.end(),
        [](const edge_t& e1, const edge_t& e2){
            return std::get<0>(e1) < std::get<0>(e2);
        });
    for (const edge_t& e : mst) {
        std::cout << std::get<0>(e) << '-' << std::get<1>(e)
            << ' ' << std::get<2>(e) << '\n';
    }
    return 0;
}
