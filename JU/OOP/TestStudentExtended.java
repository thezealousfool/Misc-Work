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
        return String.format("%-20s%-7s%-20s%-20s%-35s%-12s%-12s%-12s%-12s%-12s%-12s\n", name, String.valueOf(roll), department, course, String.valueOf(admissionDate), String.valueOf(marks[0]), String.valueOf(marks[1]), String.valueOf(marks[2]), String.valueOf(marks[3]), String.valueOf(marks[4]), String.valueOf(average));
    }
}

class StudentListExtended extends StudentList
{
    protected StudentExtended list[];

    protected Student[] getList() {
        return list;
    }

    protected StudentExtended[] getListExtended() {
        return list;
    }

    private interface PrintCriteria {
        public boolean check(StudentExtended student);
    }

    private class PrintDepartment implements PrintCriteria {
        private String department;
        public PrintDepartment(String department) {
            this.department = department;
        }
        public boolean check(StudentExtended student) {
            return department.equalsIgnoreCase(student.getDepartment());
        }
    }

    private class AvgLessThan implements PrintCriteria {
        private double value;
        public AvgLessThan(double value) {
            this.value = value;
        }
        public boolean check(StudentExtended student) {
            return value > student.getAverageMarks();
        }
    }

    private class AvgGreaterThan implements PrintCriteria {
        private double value;
        public AvgGreaterThan(double value) {
            this.value = value;
        }
        public boolean check(StudentExtended student) {
            return value < student.getAverageMarks();
        }
    }

    private class AvgLessThanOrEquals implements PrintCriteria {
        private double value;
        public AvgLessThanOrEquals(double value) {
            this.value = value;
        }
        public boolean check(StudentExtended student) {
            return value >= student.getAverageMarks();
        }
    }

    private class AvgGreaterThanOrEquals implements PrintCriteria {
        private double value;
        public AvgGreaterThanOrEquals(double value) {
            this.value = value;
        }
        public boolean check(StudentExtended student) {
            return value <= student.getAverageMarks();
        }
    }

    private class AvgEquals implements PrintCriteria {
        private double value;
        public AvgEquals(double value) {
            this.value = value;
        }
        public boolean check(StudentExtended student) {
            return value == student.getAverageMarks();
        }
    }

    private class PrintAlways implements PrintCriteria {
        public boolean check(StudentExtended student) {
            return true;
        }
    }

    private String toStringGeneric(PrintCriteria test) {
        StringBuilder sB = new StringBuilder(String.format("%-20s%-7s%-20s%-20s%-35s%-12s%-12s%-12s%-12s%-12s%-12s\n", "Name", "Roll", "Department", "Course", "Admission Date", "Subject 1", "Subject 2", "Subject 3", "Subject 4", "Subject 5", "Average"));
        for(int i = 0; i < size; ++i) {
            if(test.check(getListExtended()[i]))
                sB.append(getListExtended()[i].toString());
        }
        return sB.toString();
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
            StringBuilder sB = new StringBuilder(String.format("%-20s%-7s%-20s%-20s%-35s%-12s%-12s%-12s%-12s%-12s%-12s\n", "Name", "Roll", "Department", "Course", "Admission Date", "Subject 1", "Subject 2", "Subject 3", "Subject 4", "Subject 5", "Average"));
            sB.append(list[index].toString());
            return sB.toString();
        }
    }

    public String toString() {
        return toStringGeneric(new PrintAlways());
    }

    public String toStringStudentExtendedDepartment(String department) {
        return toStringGeneric(new PrintDepartment(department));
    }

    public String toStringStudentExtendedAverageLessThan(double average) {
        return toStringGeneric(new AvgLessThan(average));
    }

    public String toStringStudentExtendedAverageLessThanOrEquals(double average) {
        return toStringGeneric(new AvgLessThanOrEquals(average));
    }

    public String toStringStudentExtendedAverageGreaterThan(double average) {
        return toStringGeneric(new AvgGreaterThan(average));
    }

    public String toStringStudentExtendedAverageGreaterThanOrEquals(double average) {
        return toStringGeneric(new AvgGreaterThanOrEquals(average));
    }

    public String toStringStudentExtendedAverageEquals(double average) {
        return toStringGeneric(new AvgEquals(average));
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
        System.out.println("5. Print Marksheet of Students of a Department");
        System.out.println("6. Print Marksheet of Students with Average Marks less than");
        System.out.println("7. Print Marksheet of Students with Average Marks greater than");
        System.out.println("8. Print Marksheet of Students with Average Marks less than or equals");
        System.out.println("9. Print Marksheet of Students with Average Marks greater than or equals");
        System.out.println("10. Print Marksheet of Students with Average Marks equals");        
        System.out.println("11. Exit");
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
                        System.out.println(sl.toStringStudentExtended(roll));
                    }
                    break;
                case 4:
                    {
                        System.out.println(sl);
                    }
                    break;
                case 5:
                    {
                        System.out.print("Enter department name: ");
                        String department = bf.readLine();
                        System.out.println(sl.toStringStudentExtendedDepartment(department));
                    }
                    break;
                case 6:
                    {
                        System.out.print("Enter value: ");
                        double value = Double.parseDouble(bf.readLine());
                        System.out.println(sl.toStringStudentExtendedAverageLessThan(value));
                    }
                    break;
                case 7:
                    {
                        System.out.print("Enter value: ");
                        double value = Double.parseDouble(bf.readLine());
                        System.out.println(sl.toStringStudentExtendedAverageGreaterThan(value));
                    }
                    break;
                case 8:
                    {
                        System.out.print("Enter value: ");
                        double value = Double.parseDouble(bf.readLine());
                        System.out.println(sl.toStringStudentExtendedAverageLessThanOrEquals(value));
                    }
                    break;
                case 9:
                    {
                        System.out.print("Enter value: ");
                        double value = Double.parseDouble(bf.readLine());
                        System.out.println(sl.toStringStudentExtendedAverageGreaterThanOrEquals(value));
                    }
                    break;
                case 10:
                    {
                        System.out.print("Enter value: ");
                        double value = Double.parseDouble(bf.readLine());
                        System.out.println(sl.toStringStudentExtendedAverageEquals(value));
                    }
                    break;
                case 11:
                    break;
                default:
                    System.out.println("Invalid Entry!");
            }
            if(choice == 11)
                break;
        }
    }
}