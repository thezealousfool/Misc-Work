#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using std::cout;
using std::cin;

const std::string filenames[] = {"books.txt", "journals.txt", "student.txt", "faculty.txt", "transactions.txt"};

class Date
{
    int d, m, y;
    
    public:
    Date() {
        setValues(0, 0, 0);
    }

    Date(int day, int month, int year) {
        setValues(day, month, year);
    }

    void setValues(int day, int month, int year) {
        d = day;
        m = month;
        y = year;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << date.d << "/" << std::setfill('0') << std::setw(2) << date.m << "/" << date.y;
        os << oss.str();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Date& date) {
        char temp;
        is >> date.d;
        is >> temp;

        if(temp != '/') {
            date.d = 0;
            while(is.get() != '\n');
            return is;
        }

        is >> date.m;
        is >> temp;

        if(temp != '/') {
            date.d = 0;
            date.m = 0;
            while(is.get() != '\n');
            return is;
        }

        is >> date.y;

        return is;
    }
};

class Book
{
    std::string n;
    int id;

    public:
    Book(std::string name = "", int book_id = 0) : n(name), id(book_id) {
    }

    void setValues(std::string name = "", int book_id = 0) {
        n = name;
        id = book_id;
    }
};

class BookEntry
{
    Book b;
    int qty;

    public:
    BookEntry(Book book = Book(), int quantity = 0) : b(book), qty(quantity) {
    }

    void setValues(Book book = Book(), int quantity = 0) {
        b = book;
        qty = quantity;
    }
};

class Journal
{
    std::string n;
    int id, i_no, v_no;
    Date p_date;

    public:
    Journal(std::string name = "", int journal_id = 0, int issue_no = 0, int volume_no = 0, Date publish_date = Date())
    : n(name), id(id), i_no(issue_no), v_no(volume_no), p_date(publish_date) {
    }

    void setValues(std::string name = "", int journal_id = 0, int issue_no = 0, int volume_no = 0, Date publish_date = Date()){
        n = name;
        id = id;
        i_no = issue_no;
        v_no = volume_no;
        p_date = publish_date;
    }
};

class JournalEntry
{
    Journal j;
    int qty;

    public:
    JournalEntry(Journal journal = Journal(), int quantity = 0) : j(journal), qty(quantity) {
    }

    void setValues(Journal journal = Journal(), int quantity = 0) {
        j = journal;
        qty = quantity;
    }
};

int main() {
    cout << "Library System\n";
    cout << "1. Add Entry\n";
    cout << "2. Issue Entry\n";
    cout << "3. Return Entry\n";
    cout << "4. Exit\n";
    while(true) {
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        switch(choice) {
            case 1:
                {
                    cout << "\t1. Add Book\n";
                    cout << "\t2. Add Journal\n";
                    cout << "\tEnter choice: ";
                    int sub_choice;
                    cin >> sub_choice;
                    if(sub_choice == 1) {
                        std::string b_name, b_
                    } else if(sub_choice == 2) {
                    } else {
                    }
                }
                break;
            case 2:
                {
                }
                break;
            case 3:
                {
                }
                break;
            case 4:
                break;
            default: cout << "Invalid Entry!\n";
        }
        if(choice == 4)
            break;
    }
    return 0;
}