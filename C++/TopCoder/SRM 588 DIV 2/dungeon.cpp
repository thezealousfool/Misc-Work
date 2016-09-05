#include <iostream>
#include <vector>

class KeyDungeonDiv2 {
public:
    int countDoors(std::vector<int> doorR, std::vector<int> doorG, std::vector<int> keys) {
        int count = 0, reqR = 0, reqG = 0;
        for (int i=0; i<doorR.size(); ++i) {
            reqR = (doorR[i] - keys[0]);
            reqR = reqR<0 ? 0 : reqR;
            reqG = (doorG[i] - keys[1]);
            reqG = reqG<0 ? 0 : reqG;
            if ((reqR + reqG) <= keys[2]) {
                ++count;
            }
        }
        return count;
    }
};

int main() {

}