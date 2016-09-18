#include <iostream>
#include <vector>

typedef int Int;
void add_element (const std::vector<Int>& input, Int index, Int& sum) {
    if (index==input.size()-1) {
        sum += input[index];
        std::cout << sum << std::endl;
        sum -= input[index];
        return;
    }
    sum += input[index];
    for (Int i = index+1; i<input.size(); ++i) {
        add_element(input, i, sum);
    }
    std::cout << sum << std::endl;
    sum -= input[index];
    return;
}

int main() {
    std::vector<int> v = {2,3,5};
    int sum = 0;
    for (int i=0; i<v.size(); ++i) {
        add_element(v, i, sum);
    }
    return 0;
}