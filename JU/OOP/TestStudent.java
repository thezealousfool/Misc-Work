import java.io.*;
import java.util.*;

class Student
{
    protected int roll, marks[];
    protected double average;
    protected String name, course;
    protected Date admissionDate;

    public Student() {
        setValues("", 0, new int[5], "", new Date());
    }

    public Student(String name, int roll, String course, Date admissionDate) {
        setValues(name, roll, new int[5], course, admissionDate);
    }

    public Student(String name, int roll, int marks[], String course, Date admissionDate) {
        setValues(name, roll, marks, course, admissionDate);
    }

    public void setValues(String name, int roll, String course, Date admissionDate) {
        setValues(name, roll, new int[5], course, admissionDate);
    }

    public void setValues(String name, int roll, int marks[], String course, Date admissionDate) {
        this.name = name;
        this.roll = roll;
        this.marks = marks;
        this.course = course;
        this.admissionDate = admissionDate;
        this.average = (marks[0] + marks[1] + marks[2] + marks[3] + marks[4]) / 5.0;
    }

    public void setMarks(int marks[]) {
        this.marks = marks;
        this.average = (marks[0] + marks[1] + marks[2] + marks[3] + marks[4]) / 5.0;
    }

    public int[] getMarks() {
        return marks;
    }

    public double getAverageMarks() {
        return average;
    }

    public String getName() {
        return name;
    }

    public String getCourse() {
        return course;
    }

    public int getRoll() {
        return roll;
    }

    public Date getAdmissionDate() {
        return admissionDate;
    }

    public String toString() {
        return String.format("%-30s%-7s%-30s%-35s%-12s%-12s%-12s%-12s%-12s%-12s\n", name, String.valueOf(roll), course, String.valueOf(admissionDate), String.valueOf(marks[0]), String.valueOf(marks[1]), String.valueOf(marks[2]), String.valueOf(marks[3]), String.valueOf(marks[4]), String.valueOf(average));
    }
}

class StudentList
{
    protected Student list[];
    protected int size;
    protected int capacity;

    protected Student[] getList() {
        return list;
    }

    public StudentList() {
        size = 0;
        allocate(10);
    }

    public StudentList(int noStudents) {
        size = 0;
        allocate(noStudents);
    }

    public void allocate(int noStudents) {
        list = new Student[noStudents];
        capacity = noStudents;
    }

    public int getStudentsAdmitted() {
        return size;
    }

    public boolean addStudent(Student s) {
        if(capacity == size-1)
            return false;
        list[size] = s;
        ++size;
        return true;
    }

    public int searchStudent(int roll) {
        Student[] l = getList();
        for(int i = 0; i < size; ++i) {
            if(l[i].getRoll() == roll)
                return i;
        }
        return -1;
    }

    public boolean addStudent(String name, int roll, String course, Date admissionDate) {
        Student s = new Student(name, roll, course, admissionDate);
        return addStudent(s);
    }

    public boolean addStudent(String name, int roll, int marks[], String course, Date admissionDate) {
        Student s = new Student(name, roll, marks, course, admissionDate);
        return addStudent(s);
    }

    protected boolean _setMarks(int index, int marks[]) {
        if(index >= capacity)
            return false;
        getList()[index].setMarks(marks);
        return true;
    }

    public boolean setMarks(int roll, int marks[]) {
        int index = searchStudent(roll);
        if(index == -1)
            return false;
        return _setMarks(index, marks);
    }

    public String toStringStudent(int roll) {
        int index = searchStudent(roll);
        if(index == -1)
            return "";
        else {
            StringBuilder sB = new StringBuilder(String.format("%-30s%-7s%-30s%-35s%-12s%-12s%-12s%-12s%-12s%-12s\n", "Name", "Roll", "Course", "Admission Date", "Subject 1", "Subject 2", "Subject 3", "Subject 4", "Subject 5", "Average"));
            sB.append(list[index].toString());
            return sB.toString();
        }
    }

    public String toString() {
        StringBuilder sB = new StringBuilder(String.format("%-30s%-7s%-30s%-35s%-12s%-12s%-12s%-12s%-12s%-12s\n", "Name", "Roll", "Course", "Admission Date", "Subject 1", "Subject 2", "Subject 3", "Subject 4", "Subject 5", "Average"));
        for(int i = 0; i < size; ++i) {
            sB.append(list[i].toString());
        }
        return sB.toString();
    }
}

public class TestStudent
{
    public static void main(String args[]) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("1. Add Student");
        System.out.println("2. Set Marks");
        System.out.println("3. Print Marksheet of Student");
        System.out.println("4. Print Marksheet of all Students");
        System.out.println("5. Exit");
        StudentList sl = new StudentList(100);
        while(true) {
            System.out.print("Enter choice: ");
            int choice = Integer.parseInt(bf.readLine());
            switch(choice) {
                case 1:
                    {
                        System.out.print("Name: ");
                        String name = bf.readLine();
                        System.out.print("Roll: ");
                        int roll = Integer.parseInt(bf.readLine());
                        System.out.print("Course: ");
                        String course = bf.readLine();
                        if(sl.addStudent(name, roll, course, new Date()))
                            System.out.println("Successful\n");
                        else
                            System.out.println("Failed\n");                        
                    }
                    break;
                case 2:
                    {
                        System.out.print("Enter roll: ");
                        int roll = Integer.parseInt(bf.readLine());
                        System.out.println("Enter Marks of 5 subjects:");
                        int marks0 = Integer.parseInt(bf.readLine());
                        int marks1 = Integer.parseInt(bf.readLine());
                        int marks2 = Integer.parseInt(bf.readLine());
                        int marks3 = Integer.parseInt(bf.readLine());
                        int marks4 = Integer.parseInt(bf.readLine());
                        int marks[] = {marks0, marks1, marks2, marks3, marks4};
                        if(sl.setMarks(roll, marks))
                            System.out.println("Successful\n");
                        else
                            System.out.println("Failed\n");                        
                    }
                    break;
                case 3:
                    {
                        System.out.print("Enter roll: ");
                        int roll = Integer.parseInt(bf.readLine());
                        System.out.println(sl.toStringStudent(roll));
                    }
                    break;
                case 4:
                    {
                        System.out.println(sl);
                    }
                    break;
                case 5:
                    break;
                default:
                    System.out.println("Invalid Entry!");
            }
            if(choice == 5)
                break;
        }
    }
}