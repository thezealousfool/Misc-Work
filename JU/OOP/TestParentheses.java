import java.io.*;

class CharStack
{
    char[] stack;
    int length, capacity;

    public CharStack() {
        allocate(10);
    }

    public CharStack(int size) {
        allocate(size);
    }

    public void allocate(int size) {
        this.stack = new char[size];
        this.capacity = size;
        this.length = 0;
    }

    public char top() {
        if (isEmpty())
            return '\0';
        return this.stack[this.length - 1];
    }

    public boolean push(char c) {
        if(isFull())
            return false;
        this.stack[this.length] = c;
        this.length++;
        return true;
    }

    public boolean pop() {
        if (isEmpty())
            return false;
        this.length--;
        return true;
    }

    public boolean isEmpty() {
        return (this.length == 0);
    }

    public boolean isFull() {
        return (this.length == this.capacity);
    }
}

class Parentheses
{
    String data;
    CharStack stack;

    public Parentheses(String s) {
        this.data = s;
        stack = new CharStack(s.length());
    }

    public boolean check() {
        int len = this.data.length();
        for (int i = 0; i < len; ++i) {
            char ch = this.data.charAt(i);
            char invCh = '\0';
            switch (ch) {
                case ')': invCh = '('; break;
                case '}': invCh = '{'; break;
                case ']': invCh = '['; break;
            }
            switch (ch) {
                case '(':
                case '{':
                case '[':
                    stack.push(ch);
                    break;
                case ')':
                case '}':
                case ']':
                    if ((!stack.isEmpty()) && (stack.top() == invCh)) {
                        stack.pop();
                    } else {
                        while (!stack.isEmpty())
                            stack.pop();
                        return false;
                    }
            }
        }
        if (stack.isEmpty()) {
            return true;
        } else {
            while (!stack.isEmpty())
                stack.pop();
            return false;
        }
    }
}

class TestParentheses
{
    public static void main(String[] args) throws IOException {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        System.out.print("Enter string: ");
        Parentheses p = new Parentheses(br.readLine());
        if (p.check())
            System.out.println("True\n");
        else
            System.out.println("False\n");
    }
}