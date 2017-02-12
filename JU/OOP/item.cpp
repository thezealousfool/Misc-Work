#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class Item
{
    friend class ItemList;
    int c;
    double r;
    std::string n;
    
    public:
    Item() {
        this -> setParams(0, "", 0.0);
    }
    
    Item(int code, std::string name, double rate) {
        this -> setParams(code, name, rate);
    }

    void setParams(int code, std::string name, double rate) {
        c = code;
        n = name;
        r = rate;
    }

    void prettyPrint() {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(10) << c;
        std::cout << std::setw(70) << n;
        std::cout << std::setw(20) << r;
        std::cout.unsetf(std::ios::left);
    }

    friend std::ostream& operator<< (std::ostream& os, Item& i) {
        std::cout << "[" << i.c << ", " << i.n << ", " << i.r << "]";
        return os;
    }
};

class ItemList
{
    std::vector< std::pair<Item, int> > list;
    
    public:
    ItemList() {
        this -> reserveSpace(5);
    }

    ItemList(int n) {
        this -> reserveSpace(n);
    }

    void reserveSpace(int n) {
        list.reserve(n);
    }

    int existsInList(int code) {
        for(int i = 0; i < list.size(); ++i) {
            if(list[i].first.c == code)
                return i;
        }
        return -1;
    }

    int available(int code) {
        int idx;
        if((idx = existsInList(code)) != -1)
            if(list[idx].second > 0)
                return idx;
        return -1;
    }

    void updateItemIndex(int index, const Item& item) {
        list[index].first.n = item.n;
        list[index].first.r = item.r;
    }

    bool updateItem(const Item& item) {
        int idx;
        if((idx = existsInList(item.c)) != -1) {
            list[idx].first.r = item.r;
            return true;
        }
        return false;
    }

    bool updateRate(int code, double rate) {
        Item iTemp(code, "", rate);
        return updateItem(iTemp);
    }

    void addItem(Item& item) {
        int idx;
        if((idx = existsInList(item.c)) != -1) {
            ++(list[idx].second);
        } else {
            list.push_back(std::make_pair(item, 1));
        }
    }

    void addItem(Item& item, int quantity) {
        while(quantity--) {
            addItem(item);
        }
    }

    bool issueItem(int code) {
        int idx;
        if((idx = available(code)) != -1) {
            --(list[idx].second);
            return true;
        }
        return false;
    }

    void printItem(int code) {
        int idx;
        if((idx = existsInList(code)) != -1) {
            std::cout.setf(std::ios::left);
            std::cout << std::setw(13) << "Quantity";
            std::cout << std::setw(10) << "Code";
            std::cout << std::setw(70) << "Item Name";
            std::cout << std::setw(20) << "Rate" << "\n";
            std::cout << std::setw(13) << list[idx].second;
            list[idx].first.prettyPrint();
            std::cout << "\n";
            std::cout.unsetf(std::ios::left);
        } else {
            std::cout << "Item not found.\n";
        }
    }

    void prettyPrint() {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(13) << "Quantity";
        std::cout << std::setw(10) << "Code";
        std::cout << std::setw(70) << "Item Name";
        std::cout << std::setw(20) << "Rate" << "\n";
        for(std::pair<Item, int>& i : list) {
            std::cout << std::setw(13) << i.second;
            i.first.prettyPrint();
            std::cout << "\n";
        }
        std::cout.unsetf(std::ios::left);
    }

    friend std::ostream& operator<<(std::ostream& os, ItemList& il) {
        for(std::pair<Item, int>& i : il.list) {
            os << "[" << i.first << ", " << i.second << "]";
        }
        return os;
    }
};

int main()
{
    std::cout << "Item List:\n";
    std::cout << "1. Add Item\n";
    std::cout << "2. Update Item rate\n";
    std::cout << "3. Issue Item\n";
    std::cout << "4. Display List\n";
    std::cout << "5. Display Item\n";
    std::cout << "6. Exit\n";
    int choice;
    ItemList list;
    while(true) {
        std::cout << "Enter choice: ";
        std::cin >> choice;
        switch(choice) {
            case 1:
                    {
                        int c, q;
                        double r;
                        std::string n;

                        std::cout << "Item code: "; std::cin >> c;
                        std::cout << "Name: "; std::cin >> n;
                        std::cout << "Rate: "; std::cin >> r;
                        std::cout << "Quantity: "; std::cin >> q;
                        Item iTemp(c, n, r);
                        list.addItem(iTemp, q);
                    }
                    break;
            case 2: {
                        int c, r;
                        std::cout << "Item code: "; std::cin >> c;
                        std::cout << "Rate: "; std::cin >> r;
                        if(list.updateRate(c, r)) {
                            std::cout << "Item rate updated.\n";
                        } else {
                            std::cout << "Update Unsuccessful.\n";
                        }
                    }
                    break;
            case 3: {
                        int c;
                        std::cout << "Item code: "; std::cin >> c;
                        if(list.issueItem(c)) {
                            std::cout << "Item issued.\n";
                        } else {
                            std::cout << "Issue Unsuccessful.\n";
                        }
                    }
                    break;
            case 4:
                    list.prettyPrint();
                    break;
            case 5: {
                        int c;
                        std::cout << "Item code: "; std::cin >> c;
                        list.printItem(c);
                    }
                    break;
            case 6:
                    break;
            default:
                    std::cout << "Invalid Choice!\n";
        }
        if(choice == 6)
            break;
    }
}