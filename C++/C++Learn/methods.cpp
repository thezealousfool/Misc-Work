#include <iostream>
#include <string>

struct hello {
    int roll;
    std::string name;
    void operator() () {
        std::cout << "Name: " << (*this).name << "\nRoll no: " << (*this).roll << "\n\n";
    }
};

int main() {
    hello h1 {1, "Vivek"};
    hello h2 {2, "Polu"};
    h1();
    h2();
    return 0;
}