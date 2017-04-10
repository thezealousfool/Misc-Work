#include <iostream>
#include <array>
#define TYPES 4

enum class vehicle
{
    two_wheeler = 1,
    light_motor_vehicle = 2,
    heavy_motor_vehicle = 3,
    super_heavy_motor_vehicle = 4
};

class tolltax
{
    double amount;
    std::array<int, TYPES> no_of_vehicles;
    const std::array<double, TYPES> cost = {{10, 20, 30, 40}};

    public:
    tolltax()
    {
        no_of_vehicles = {{0, 0, 0, 0}};
    }
    void receive_toll(vehicle v) {
        amount += cost[(int)v - 1];
        no_of_vehicles[(int)v - 1]++;
    }

    double amount_collected() {
        return amount;
    }

    int no_of_vehicles_crossed(vehicle v) {
        return no_of_vehicles[(int)v - 1];
    }

    int no_of_vehicles_crossed() {
        int total = 0;
        for(int i = 0; i < TYPES; ++i)
            total += no_of_vehicles[i];
        return total;
    }
};

int main()
{
    std::cout << "Toll Tax:\n";
    std::cout << "1. Receive Toll\n";
    std::cout << "2. Display Amount\n";
    std::cout << "3. No of vehicles\n";
    std::cout << "4. Exit\n";

    tolltax t;
    while(true) {
        int choice;
        std::cout << "Enter choice: ";
        std::cin >> choice;
        switch(choice) {
            case 1:
                std::cout << "\tVehicle type: \n";
                std::cout << "\t1. Two Wheeler\n";
                std::cout << "\t2. Light Motor Vehicle\n";
                std::cout << "\t3. Heavy Motor Vehicle\n";
                std::cout << "\t4. Super Heavy Motor Vehicle\n";
                std::cout << "\tEnter choice: ";
                int type;
                std::cin >> type;
                switch(type) {
                    case 1: t.receive_toll(vehicle::two_wheeler); break;
                    case 2: t.receive_toll(vehicle::light_motor_vehicle); break;
                    case 3: t.receive_toll(vehicle::heavy_motor_vehicle); break;
                    case 4: t.receive_toll(vehicle::super_heavy_motor_vehicle); break;
                }
                break;
            case 2:
                std::cout << "Total Toll collected: ";
                std::cout << t.amount_collected() << "\n";
                break;
            case 3:
                std::cout << "\tNo of vehicles crossed:\t" << t.no_of_vehicles_crossed() << "\n";
                std::cout << "\tTwo Wheeler: \t\t" << t.no_of_vehicles_crossed(vehicle::two_wheeler) << "\n";
                std::cout << "\tLight Motor Vehicle: \t" << t.no_of_vehicles_crossed(vehicle::light_motor_vehicle) << "\n";
                std::cout << "\tHeavy Wheeler: \t\t" << t.no_of_vehicles_crossed(vehicle::heavy_motor_vehicle) << "\n";
                std::cout << "\tSuper Heavy Wheeler: \t" << t.no_of_vehicles_crossed(vehicle::super_heavy_motor_vehicle) << "\n";
                break;
            case 4:
                break;
            default:
                std::cout << "Wrong Input\n";
                break;
        }
        if(choice == 4)
            break;
    }
    return 0;
}