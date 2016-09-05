import java.util.Scanner;

public class TakingInput {

    public static void main (String[] args) {
        Scanner input = new Scanner(System.in);
        int[] array = new int[10];
        System.out.print("Enter 10 numbers: ");
        for (int i = 0; i < 10; ++i) {
            array[i] = input.nextInt();
        }
        for (int e : array) {
            System.out.println(e);
        }
    }

}