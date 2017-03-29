import java.io.*;
import java.util.*;

class Balance
{
    String accountNo;
    double balance;
    Date lastUpdation;
    boolean error;

    public String getAccountNo() {
        return this.accountNo;
    }

    public double getBalance() {
        return this.balance;
    }

    public Date getLastUpdation() {
        return this.lastUpdation;
    }

    public void setBalance(double balance) {
        if (balance < 500) {
            error = true;
            return;
        }
        this.balance = balance;
    }

    public void setUpdationDate(Date lastUpdation) {
        this.lastUpdation = lastUpdation;
    }

    public Balance() {
        setValues("", 0.0, new Date());
    }

    public Balance(String accountNo, double balance) {
        setValues(accountNo, balance, new Date());
    }

    public void setValues(String accountNo, double balance, Date lastUpdation) {
        if(balance < 500) {
            this.error = true;
            return;
        }
        this.accountNo = accountNo;
        this.balance = balance;
        this.lastUpdation = lastUpdation;
        this.error = false;
    }

    public void setValues(String accountNo, double balance) {
        setValues(accountNo, balance, new Date());
    }

    public boolean validate() {
        return !this.error;
    }
}

class Transaction
{
    String accountNo;
    Date date;
    double amount;
    char type;

    public Transaction(String accountNo, double amount, char type, Date date) {
        setValues(accountNo, amount, type, date);
    }

    public Transaction(String accountNo, double amount, char type) {
        setValues(accountNo, amount, type);
    }    

    public void setValues(String accountNo, double amount, char type, Date date) { 
        this.accountNo = accountNo;
        this.date = date;
        this.amount = amount;
        this.type = type;
    }

    public void setValues(String accountNo, double amount, char type) { 
        setValues(accountNo, amount, type, new Date());
    }

    public boolean transact(Balance b) {
        if (!b.getAccountNo().equals(this.accountNo) || this.amount < 0)
            return false;
        if (type == 'd') {
            if (b.getBalance() - this.amount < 500)
                return false;
            b.setBalance(b.getBalance() - this.amount);
            b.setUpdationDate(new Date());
            return true;
        } else if (type == 'c') {
            b.setBalance(b.getBalance() + this.amount);
            b.setUpdationDate(new Date());
            return true;
        }
        return false;
    }
}

class TestBalance
{
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("1. Create Account");
        System.out.println("2. Print Details");
        System.out.println("3. Credit Transaction");
        System.out.println("4. Debit Transaction");
        System.out.println("5. Exit");
        Balance b = new Balance();
        while(true) {
            System.out.print("Enter choice: ");
            int choice = Integer.parseInt(bf.readLine());
            switch(choice) {
                case 1:
                    {
                        System.out.print("Account No: ");
                        String accNo = bf.readLine();
                        System.out.print("Balance: ");
                        double bal = Double.parseDouble(bf.readLine());
                        b.setValues(accNo, bal);
                        if (b.validate())
                            System.out.println("Successful\n");
                        else
                            System.out.println("Failed\n");
                    }
                    break;
                case 2:
                    {
                        if (b.validate()) {
                            System.out.println("Account No: \t\t" + b.getAccountNo());
                            System.out.println("Balance: \t\t" + b.getBalance());
                            System.out.println("Last Updated: \t\t" + b.getLastUpdation());
                            System.out.println();
                        } else {
                            System.out.println("Have a valid account setup first.\n");
                        }
                    }
                    break;
                case 3:
                case 4:
                    {
                        Transaction t;
                        System.out.print("Accountc No: ");
                        String accNo = bf.readLine();
                        System.out.print("Amount: ");
                        double amt = Double.parseDouble(bf.readLine());
                        char typ = '\0';
                        if (choice == 3)
                            typ = 'c';
                        else if (choice == 4)
                            typ = 'd';
                        t = new Transaction(accNo, amt, typ);
                        if (t.transact(b))
                            System.out.println("Transaction Successful\n");
                        else
                            System.out.println("Transaction Failed\n");
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