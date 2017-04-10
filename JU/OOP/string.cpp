#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::setw;

class myString
{
    char* arr;
    int len;
    
    public:
    myString() {
        arr = NULL;
        len = 0;
    }

    myString(int size, char value = '\0') {
        arr = NULL;
        len = 0;
        allocate(size, value);
    }

    myString(const myString& a) {
        arr = new char[a.len];
        len = a.len;
        for(int i = 0; i < len; ++i)
            arr[i] = a[i];
    }

    myString(int size, char* a) {
        arr = NULL;
        len = 0;
        allocate(size, a);
    }

    void allocate(int size, char* value) {
        if(arr != NULL) {
            delete[] arr;
            arr = NULL;
        }
        arr = new char[size];
        len = size;
        for(int i = 0; i < len; ++i)
            arr[i] = value[i];
    }

    void allocate(int size, char value) {
        if(arr != NULL) {
            delete[] arr;
            arr = NULL;
        }
        arr = new char[size];
        len = size;
        for(int i = 0; i < size; ++i){
            arr[i] = value;
        }
    }

    char& operator[](int idx) {
        return arr[idx];
    }

    const char& operator[](int idx) const {
        return arr[idx];
    }

    myString& operator=(const myString& a) {
        if(arr == NULL) {
            arr = new char[a.len];
        }
        else {
            delete[] arr;
            arr = NULL;
            arr = new char[a.len];
        }
        len = a.len;
        for(int i = 0; i < a.len; ++i)
            arr[i] = a[i];
        return (*this);
    }

    friend bool operator<(const myString& a1, const myString& a2) {
        bool equal = true;
        for(int i = 0; i < std::min(a1.len, a2.len); ++i) {
            if(a1[i] == a2[i])
                equal = equal && true;
            else if(a1[i] < a2[i])
                equal = false;
            else
                return false;
        }
        if(equal) {
            if(a1.len < a2.len)
                return true;
            else
                return false;
        }
        return true;
    }

    friend bool operator>(const myString& a1, const myString& a2) {
        bool equal = true;
        for(int i = 0; i < std::min(a1.len, a2.len); ++i) {
            if(a1[i] == a2[i])
                equal = equal && true;
            else if(a1[i] > a2[i])
                equal = false;
            else
                return false;
        }
        if(equal) {
            if(a1.len > a2.len)
                return true;
            else
                return false;
        }
        return true;
    }
    
    friend bool operator==(const myString& a1, const myString& a2) {
        if(a1.len != a2.len)
            return false;
        for(int i = 0; i < a1.len; ++i) {
            if(a1[i] != a2[i])
                return false;
        }
        return true;
    }

    friend bool operator<=(const myString& a1, const myString& a2) {
        return !(a1 > a2);
    }

    friend bool operator>=(const myString& a1, const myString& a2) {
        return !(a1 < a2);
    }

    friend bool operator!=(const myString& a1, const myString& a2) {
        return !(a1 == a2);
    }

    friend myString operator+(const myString& a1, const myString& a2) {
        myString res(a1.len + a2.len);
        int i = 0;
        for(; (i < a1.len) && (a1[i] != '\0'); ++i)
            res[i] = a1[i];
        for(int j = 0; (j < a2.len) && (a2[j] != '\0'); ++j, ++i)
            res[i] = a2[j];
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const myString& a) {
        for(int i = 0; (i < a.len) && (a[i] != '\0'); ++i) {
            os << a[i];
        }
        return os;
    }

    ~myString() {
        if(arr != NULL) {
            delete[] arr;
            arr = NULL;
        }
    }
};

int main(void)
{
    cout << "Array:\n";
    cout << "1. Initialise\n";
    cout << "2. Add\n";
    cout << "3. Compare\n";
    cout << "4. Exit\n";

    while(true) {
        int choice;
        myString a1, a2, a3;
        cout << "Enter choice: ";
        cin >> choice;
        cin.get();
        switch(choice) {
            case 1: {
                        char str[100];
                        cout << "Value: ";
                        cin.getline(str, 100);
                        a1.allocate(100, str);
                        cout << "Input successful!\n" << a1 << "\n";
                    }
                    break;
            case 2: {
                        char str[100];
                        cout << "String 1:\n";
                        cout << "Value: ";
                        cin.getline(str, 100);
                        a1.allocate(100, str);
                        cout << "String 2:\n";
                        cout << "Value: ";
                        cin.getline(str, 100);
                        a2.allocate(100, str);
                        a3 = a1 + a2;
                        cout << "   " << a1 << "\n";
                        cout << " + " << a2 << "\n";
                        cout << " = " << a3 << "\n";
                    }
                    break;
            case 3: {
                        char str[100];
                        cout << "String 1:\n";
                        cout << "Value: ";
                        cin.getline(str, 100);
                        a1.allocate(100, str);
                        cout << "String 2:\n";
                        cout << "Value: ";
                        cin.getline(str, 100);
                        a2.allocate(100, str);
                        bool comp;
                        cout.setf(std::ios::left);
                        cout << setw(15) << "Less than";
                        cout << setw(15) << "Greater than";
                        cout << setw(15) << "Equal";
                        cout << setw(25) << "Less than or Equal";
                        cout << setw(25) << "Greater than or Equal";
                        cout << setw(15) << "Not Equal";
                        cout << "\n";
                        comp = a1 < a2;
                        if(comp) cout << setw(15) << "True";
                        else cout << setw(15) << "False";
                        comp = a1 > a2;
                        if(comp) cout << setw(15) << "True";
                        else cout << setw(15) << "False";
                        comp = a1 == a2;
                        if(comp) cout << setw(15) << "True";
                        else cout << setw(15) << "False";
                        comp = a1 <= a2;
                        if(comp) cout << setw(25) << "True";
                        else cout << setw(25) << "False";
                        comp = a1 >= a2;
                        if(comp) cout << setw(25) << "True";
                        else cout << setw(25) << "False";
                        comp = a1 != a2;
                        if(comp) cout << setw(15) << "True";
                        else cout << setw(15) << "False";
                        cout << "\n";
                        cout.unsetf(std::ios::left);
                    }
                    break;
            case 4: break;
            default:
                cout << "Wrong Input\n";
                break;
        }
        if(choice == 4)
            break;
    }
    return 0;
}