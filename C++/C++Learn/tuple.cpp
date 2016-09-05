#include <iostream>
#include <tuple>

int main() {
    std::tuple <int,int,double> first = std::make_tuple(1,2,22.5);
    std::cout << std::get<0>(first) << " " << std::get<1>(first) << "-" << std::get<2>(first) << std::endl;
    return 0;
}