import java.util.Scanner;
import java.util.Stack;

public class BodmasEvaluate {

    private static boolean greaterPrecedence (char c1, char c2) {
        switch (c2) {
            case '*' :
            case '/' : return false;
            case '+' :
            case '-' : if (c1 != '+' && c1 != '-' && c1 != '(') return true;
                else return false;
        }
        return false;
    }

    private static String toPostfix (String infix) {
        int index = 0;
        char temp;
        Stack<Character> stack = new Stack<Character>();
        String postfix = "";
        while (index < infix.length()) {
            temp = infix.charAt(index);
            if (temp >= '0' && temp <= '9') {
                postfix += Character.toString(temp);
            }
            else if (temp == '(') {
                stack.push(temp);
            }
            else if (temp == ')') {
                while (stack.size() > 0) {
                    temp = (char)stack.pop();
                    if (temp == '(')
                        break;
                    else
                        postfix += Character.toString(temp);
                }
            }
            else {
                while (stack.size() > 0 && greaterPrecedence((char)stack.peek(), temp)) {
                    postfix += Character.toString((char)stack.pop());
                }
                stack.push(temp);
            }
            ++index;
        }
        while (stack.size() > 0)
            postfix += Character.toString((char)stack.pop());
        return postfix;
    }

    private static double evaluatePostfix (String postfix) {
        Stack<Double> stack = new Stack<Double>();
        int index = 0;
        char temp;
        while (index < postfix.length()) {
            temp = postfix.charAt(index);
            if (temp >= '0' && temp <= '9') {
                stack.push((double)(temp - '0'));
            }
            else {
                double right = (double)stack.pop();
                double left = (double)stack.pop();
                switch (temp) {
                    case '+' : stack.push(left+right); break;
                    case '-' : stack.push(left-right); break;
                    case '*' : stack.push(left*right); break;
                    case '/' : stack.push(left/right); break;
                }
            }
            ++index;
        }
        return (double)stack.pop();
    }

    public static void main (String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter expression: ");
        String infix = input.nextLine();
        String postfix = toPostfix(infix);
        System.out.println(postfix);
        double value = evaluatePostfix(postfix);
        System.out.println("Value: " + value);
    }

}