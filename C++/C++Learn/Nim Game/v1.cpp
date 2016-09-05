#include <iostream>
#include <array>

std::array<std::array<bool, 7>, 3> nim;

inline user1() {
    std::cout << "User 1's turn: \n";
}

inline user2() {
    std::cout << "User 2's turn: \n";
}

inline error() {
    std::cout << "Error!!\n";
}

inline print() {
    int end;
    for(int i=0; i<3; ++i) {
        switch(i) {
            case 0 : end = 3; break;
            case 1 : end = 5; break;
            case 2 : end = 7; break;
        }
        for (int j=0; j<end; ++j) {
            nim[i][j] ? std::cout << "x " : std::cout << "- ";
        }
        std::cout << "\n";
    }    
    std::cout << "\n";
}

int main() {
    {
        std::array<bool, 7> empty;
        empty.fill(false);
        nim.fill(empty);
    }
    for (int i=3; i<7; ++i)
        nim[0][i] = true;
    for (int i=5; i<7; ++i)
        nim[1][i] = true;
    int blocks_remaining = 15;
    bool winner_user1 = false;
    print();
    while (blocks_remaining > 0) {
        {
            bool user_one = false;
            while (!user_one) {
                user1();
                int row; std::cin >> row;
                int no; std::cin >> no;
                if ((row > 3) || (row == 3 && no > 7) || (row == 2 && no > 5) || (row == 1 && no > 3)) { error(); continue; }
                for (int i = 0; i < no; ++i) {
                    int temp;
                    std::cin >> temp;
                    if (nim[row-1][temp-1]) {
                        error(); user_one = false; break;
                    }
                    else {
                        user_one = true; nim[row-1][temp-1] = true;
                        --blocks_remaining;
                    }
                }
            }
        }
        print();
        if (!blocks_remaining) {
            std::cout << "User 2 wins!\n";
            return 0;
        }
        {
            bool user_two = false;
            while (!user_two) {
                user2();
                int row; std::cin >> row;
                int no; std::cin >> no;
                if ((row > 3) || (row == 3 && no > 7) || (row == 2 && no > 5) || (row == 1 && no > 3)) { error(); continue; }
                for (int i = 0; i < no; ++i) {
                    int temp;
                    std::cin >> temp;
                    if (nim[row-1][temp-1]) {
                        error(); user_two = false; break;
                    }
                    else {
                        user_two = true; nim[row-1][temp-1] = true;
                        --blocks_remaining;
                    }
                }
            }
        }
        print();
        if (!blocks_remaining) {
            std::cout << "User 1 wins!\n"; return 0;
        }
    }
    return 0;
}