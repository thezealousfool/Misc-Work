#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <array>

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

class Student
{
    int r;
    std::string n, c;
    Date admD;
    std::array<int, 5> m;

    public:
    Student() {
        setValues(0, "", "", Date(), {{0, 0, 0, 0, 0}});
    }
 
    Student(int roll, std::string name, std::string course, Date admissionDate) {
        setValues(roll, name, course, admissionDate, {{0, 0, 0, 0, 0}});
    }
 
    Student(int roll, std::string name, std::string course, Date admissionDate, std::array<int, 5> marks) {
        setValues(roll, name, course, admissionDate, marks);
    }

    void setValues(int roll, std::string name, std::string course, Date admissionDate, std::array<int, 5> marks) {
        r = roll;
        n = name;
        c = course;
        admD = admissionDate;
        m = marks;
    }

    void setMarks(std::array<int, 5> marks) {
        m = marks;
    }

    void printPretty() {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(10) << r;
        std::cout << std::setw(20) << admD;
        std::cout << std::setw(30) << n;
        std::cout << std::setw(30) << c;
        std::cout.unsetf(std::ios::left);
    }

    void printPrettyReport() {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(10) << m[0];
        std::cout << std::setw(10) << m[1];
        std::cout << std::setw(10) << m[2];
        std::cout << std::setw(10) << m[3];
        std::cout << std::setw(10) << m[4];
        std::cout << std::setw(10) << m[0] + m[1] + m[2] + m[3] + m[4];
        std::cout.unsetf(std::ios::left);
    }
};

class StudentBatch
{
    int no;
    std::vector<Student> students;

    public:
    StudentBatch() {
        no = 0;
        reserve(5);
    }

    StudentBatch(int n) {
        no = 0;
        reserve(n);
    }

    void reserve(int n) {
        students.reserve(n);
    }

    void addStudent(std::string name, std::string course, Date admissionDate) {
        students.push_back(Student(++no, name, course, admissionDate));
    }

    bool validRoll(int roll) {
        if(roll <= students.size()) 
            return true;
        else
            return false;
    }

    bool setMarks(int roll, std::array<int, 5> marks) {
        if(validRoll(roll)) {
            students[roll - 1].setMarks(marks);
            return true;
        } else {
            return false;
        }
    }

    void printPretty() {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(10) << "Roll no";
        std::cout << std::setw(20) << "Admission Date";
        std::cout << std::setw(30) << "Name";
        std::cout << std::setw(30) << "Course";
        std::cout << "\n";
        for(Student s : students) {
            s.printPretty();
            std::cout << "\n";
        }
        std::cout.unsetf(std::ios::left);
    }

    void printPrettyReport() {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(10) << "Roll no";
        std::cout << std::setw(20) << "Admission Date";
        std::cout << std::setw(30) << "Name";
        std::cout << std::setw(30) << "Course";
        std::cout << std::setw(10) << "Sub 0";
        std::cout << std::setw(10) << "Sub 1";
        std::cout << std::setw(10) << "Sub 2";
        std::cout << std::setw(10) << "Sub 3";
        std::cout << std::setw(10) << "Sub 4";
        std::cout << std::setw(10) << "Total";
        std::cout << "\n";
        for(Student s : students) {
            s.printPretty();
            s.printPrettyReport();
            std::cout << "\n";
        }
        std::cout.unsetf(std::ios::left);
    }

    void printStudent(int roll) {
        if(validRoll(roll)) {
            std::cout.setf(std::ios::left);
            std::cout << std::setw(10) << "Roll no";
            std::cout << std::setw(20) << "Admission Date";
            std::cout << std::setw(30) << "Name";
            std::cout << std::setw(30) << "Course";
            std::cout << "\n";
            students[roll - 1].printPretty();
            std::cout << "\n";
            std::cout.unsetf(std::ios::left);
        }
    }

    void printStudentReport(int roll) {
        if(validRoll(roll)) {
            std::cout.setf(std::ios::left);
            std::cout << std::setw(10) << "Roll no";
            std::cout << std::setw(20) << "Admission Date";
            std::cout << std::setw(30) << "Name";
            std::cout << std::setw(30) << "Course";
            std::cout << std::setw(10) << "Sub 0";
            std::cout << std::setw(10) << "Sub 1";
            std::cout << std::setw(10) << "Sub 2";
            std::cout << std::setw(10) << "Sub 3";
            std::cout << std::setw(10) << "Sub 4";
            std::cout << "\n";
            students[roll - 1].printPretty();
            students[roll - 1].printPrettyReport();
            std::cout << "\n";
            std::cout.unsetf(std::ios::left);
        }
    }

    int studentsAdmitted() {
        return no;
    }
};

int main()
{
    std::cout << "Item List:\n";
    std::cout << "1. Add Student\n";
    std::cout << "2. Set Marks\n";
    std::cout << "3. Display All Students' Details\n";
    std::cout << "4. Display Student Details\n";
    std::cout << "5. Display All Students' Reports\n";
    std::cout << "6. Display Student Report\n";
    std::cout << "7. Exit\n";
    int choice;
    StudentBatch batch;
    while(true) {
        std::cout << "Enter choice: ";
        std::cin >> choice;
        getchar();
        switch(choice) {
            case 1:
                    {
                        std::string n, c;
                        Date admD;

                        std::cout << "Name: "; std::getline(std::cin, n);
                        std::cout << "Course: "; std::getline(std::cin, c);
                        std::cout << "Admission Date: "; std::cin >> admD;
                        batch.addStudent(n, c, admD);
                        std::cout << "Roll: " << batch.studentsAdmitted() << "\n";
                    }
                    break;
            case 2: {
                        std::array<int, 5> inpMarks;
                        int roll;
                        std::cout << "Enter roll: ";
                        std::cin >> roll;
                        if(!batch.validRoll(roll)) {
                            std::cout << "Invalid Roll!\n";
                            continue;
                        }
                        std::cout << "Enter Marks of 5 subjects:\n";
                        for(int i = 0; i < 5; ++i) {
                            std::cin >> inpMarks[i];
                        }
                        batch.setMarks(roll, inpMarks);
                    }
                    break;
            case 3: 
                    batch.printPretty();
                    break;
            case 4: {
                        int roll;
                        std::cout << "Roll: ";
                        std::cin >> roll;
                        if(!batch.validRoll(roll)) {
                            std::cout << "Invalid Roll!\n";
                            continue;
                        }
                        batch.printStudent(roll);
                    }
                    break;
            case 5:
                    batch.printPrettyReport();
                    break;
            case 6: {
                        int roll;
                        std::cout << "Roll: ";
                        std::cin >> roll;
                        if(!batch.validRoll(roll)) {
                            std::cout << "Invalid Roll!\n";
                            continue;
                        }
                        batch.printStudentReport(roll);
                    }
            case 7: break;
            default:
                    std::cout << "Invalid Choice!\n";
        }
        if(choice == 7)
            break;
    }
    return 0;
}