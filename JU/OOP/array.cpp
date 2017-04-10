#include <iostream>
using std::cout;
using std::cin;

class myArray
{
    int* arr;
    int len;
    
    public:
    myArray() {
        arr = NULL;
        len = 0;
    }

    myArray(int size, int value = 0) {
        arr = NULL;
        len = 0;
        allocate(size, value);
    }

    myArray(const myArray& a) {
        arr = new int[a.len];
        len = a.len;
        for(int i = 0; i < len; ++i)
            arr[i] = a[i];
    }

    myArray(int size, int* a) {
        arr = NULL;
        len = 0;
        allocate(size, a);
    }

    void allocate(int size, int* value) {
        if(arr != NULL) {
            delete[] arr;
            arr = NULL;
        }
        arr = new int[size];
        len = size;
        for(int i = 0; i < len; ++i)
            arr[i] = value[i];
    }

    void allocate(int size, int value) {
        if(arr != NULL) {
            delete[] arr;
            arr = NULL;
        }
        arr = new int[size];
        len = size;
        for(int i = 0; i < size; ++i){
            arr[i] = value;
        }
    }

    int& operator[](int idx) {
        return arr[idx];
    }

    const int& operator[](int idx) const {
        return arr[idx];
    }

    myArray& operator=(const myArray& a) {
        if(arr == NULL) {
            arr = new int[a.len];
        }
        else {
            delete[] arr;
            arr = NULL;
            arr = new int[a.len];
        }
        len = a.len;
        for(int i = 0; i < a.len; ++i)
            arr[i] = a[i];
        return (*this);
    }

    friend myArray operator+(myArray a1, const myArray& a2) {
        for(int i = 0; i < std::min(a2.len, a1.len); ++i)
            a1[i] += a2[i];
        return a1;
    }

    myArray operator*(int value) const {
        myArray res(*this);
        for(int i = 0; i < len; ++i)
            res[i] *= value;
        return res;
    }

    friend myArray operator*(int value, const myArray a) {
        return a.operator*(value);
    }

    friend std::ostream& operator<<(std::ostream& os, const myArray& a) {
        os << "[";
        for(int i = 0; i < (a.len - 1); ++i) {
            os << a[i] << ", ";
        }
        if(a.len > 0) {
            os << a[a.len - 1];
        }
        os << "]";
        return os;
    }

    ~myArray() {
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
    cout << "3. Multiply\n";
    cout << "4. Exit\n";

    while(true) {
        int choice;
        myArray a1, a2, a3;
        cout << "Enter choice: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                        int size, value;
                        cout << "Size: ";
                        cin >> size;
                        cout << "Initial Value: ";
                        cin >> value;
                        a1.allocate(size, value);
                        cout << "Input successful!\n" << a1 << "\n";
                    }
                    break;
            case 2: {
                        int size, value;
                        cout << "Array 1:\n";
                        cout << "Size: ";
                        cin >> size;
                        cout << "Value: ";
                        cin >> value;
                        a1.allocate(size, value);
                        cout << "Array 2:\n";
                        cout << "Size same as Array 1\n";
                        cout << "Value: ";
                        cin >> value;
                        a2.allocate(size, value);
                        a3 = a1 + a2;
                        cout << "   " << a1 << "\n";
                        cout << " + " << a2 << "\n";
                        cout << " = " << a3 << "\n";
                    }
                    break;
            case 3: {
                        int size, value;
                        cout << "Array:\n";
                        cout << "Size: ";
                        cin >> size;
                        cout << "Value: ";
                        cin >> value;
                        a1.allocate(size, value);
                        cout << "Scalar: ";
                        cin >> value;
                        a2 = a1 * value;
                        cout << a1 << " * " << value << " = " << a2 << "\n";
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