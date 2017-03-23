import java.io.*;
import java.util.*;

class StudentExtended extends Student
{
    protected String department;

    public StudentExtended() {
        setValues("", 0, "", new int[5], "", new Date());
    }

    public StudentExtended(String name, int roll, String department, String course, Date admissionDate) {
        setValues(name, roll, department, new int[5], course, admissionDate);
    }

    public StudentExtended(String name, int roll, String department, int marks[], String course, Date admissionDate) {
        setValues(name, roll, department, marks, course, admissionDate);
    }

    public void setValues(String name, int roll, String department, int marks[], String course, Date admissionDate) {
        setValues(name, roll, marks, course, admissionDate);
        this.department = department;
    }

    public String getDepartment() {
        return department;
    }

    public String toString() {
        return String.format("%-25s%-7s%-25s%-25s%-35s%-12s%-12s%-12s%-12s%-12s\n", name, String.valueOf(roll), department, course, String.valueOf(admissionDate), String.valueOf(marks[0]), String.valueOf(marks[1]), String.valueOf(marks[2]), String.valueOf(marks[3]), String.valueOf(marks[4]));
    }
}

class StudentListExtended extends StudentList
{
    protected StudentExtended list[];

    protected Student[] getList() {
        return list;
    }

    public StudentListExtended() {
        size = 0;
        allocate(10);
    }

    public StudentListExtended(int noStudents) {
        size = 0;
        allocate(noStudents);
    }

    public void allocate(int noStudents) {
        list = new StudentExtended[noStudents];
        capacity = noStudents;
    }

    public boolean addStudentExtended(StudentExtended s) {
        if(capacity == size-1)
            return false;
        list[size] = s;
        ++size;
        return true;
    }

    public boolean addStudentExtended(String name, int roll, String department, String course, Date admissionDate) {
        StudentExtended s = new StudentExtended(name, roll, department, course, admissionDate);
        return addStudentExtended(s);
    }

    public boolean addStudentExtended(String name, int roll, String department, int marks[], String course, Date admissionDate) {
        StudentExtended s = new StudentExtended(name, roll, department, marks, course, admissionDate);
        return addStudentExtended(s);
    }

    public String toStringStudentExtended(int roll) {
        int index = searchStudent(roll);
        if(index == -1)
            return "";
        else {
            StringBuilder sB = new StringBuilder(String.format("%-25s%-7s%-25s%-25s%-35s%-12s%-12s%-12s%-12s%-12s\n", "Name", "Roll", "Department", "Course", "Admission Date", "Subject 1", "Subject 2", "Subject 3", "Subject 4", "Subject 5"));
            sB.append(list[index].toString());
            return sB.toString();
        }
    }

    public String toString() {
            StringBuilder sB = new StringBuilder(String.format("%-25s%-7s%-25s%-25s%-35s%-12s%-12s%-12s%-12s%-12s\n", "Name", "Roll", "Department", "Course", "Admission Date", "Subject 1", "Subject 2", "Subject 3", "Subject 4", "Subject 5"));
        for(int i = 0; i < size; ++i) {
            sB.append(list[i].toString());
        }
        return sB.toString();
    }
}

class TestStudentExtended
{
    public static void main(String args[]) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("1. Add Student");
        System.out.println("2. Set Marks");
        System.out.println("3. Print Marksheet of Student");
        System.out.println("4. Print Marksheet of all Students");
        System.out.println("5. Exit");
        StudentListExtended sl = new StudentListExtended(100);
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
                        System.out.print("Department: ");
                        String department = bf.readLine();
                        System.out.print("Course: ");
                        String course = bf.readLine();
                        if(sl.addStudentExtended(name, roll, department, course, new Date()))
                            System.out.println("Successful");
                        else
                            System.out.println("Failed");                        
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
                            System.out.println("Successful");
                        else
                            System.out.println("Failed");                        
                    }
                    break;
                case 3:
                    {
                        System.out.print("Enter roll: ");
                        int roll = Integer.parseInt(bf.readLine());
                        System.out.print(sl.toStringStudentExtended(roll));
                    }
                    break;
                case 4:
                    {
                        System.out.print(sl);
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