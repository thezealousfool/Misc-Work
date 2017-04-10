import java.io.*;

class Item
{
    protected int itemCode;
    protected String name;
    protected double rate;

    public Item() {
        setValues(0, "", 0.0);
    }

    public Item(int itemCode, String name, double rate) {
        setValues(itemCode, name, rate);
    }

    public void setValues(int itemCode, String name, double rate) {
        this.itemCode = itemCode;
        this.name = name;
        this.rate = rate;
    }

    public void setRate(double rate) {
        if(rate < 0)
            return;
        this.rate = rate;
    }

    public int getItemCode() { 
        return itemCode;
    }

    public String getName() { 
        return name;
    }

    public double getRate() { 
        return rate;
    }

    public String toString() {
        StringBuilder sB = new StringBuilder(String.format("%-40s%-15s%-15s", name, String.valueOf(itemCode), String.valueOf(rate)));
        return sB.toString();
    }
}

class ItemList
{
    Item[] itemList;
    int[] quantityList;
    int size, capacity;

    protected Item[] getItemList() {
        return itemList;
    }

    protected int[] getQuantityList() {
        return quantityList;
    }

    public ItemList() {
        size = 0;
        allocate(10);
    }

    public ItemList(int noOfItems) {
        size = 0;
        allocate(noOfItems);
    }

    public int getCapacity() {
        return capacity;
    }

    public int getSize() {
        return size;
    }

    public int getItemsAdded() {
        return size;
    }

    public void allocate(int noOfItems) {
        itemList = new Item[noOfItems];
        quantityList = new int[noOfItems];
        capacity = noOfItems;
    }

    public int searchItem(int code) {
        for(int i = 0; i < getSize(); ++i) {
            if(getItemList()[i].getItemCode() == code) {
                return i;
            }
        }
        return -1;
    }

    public boolean addItem(Item item, int quantity) {
        if(getCapacity() == getSize()-1)
            return false;
        if(quantity < 0)
            return false;
        int index = searchItem(item.getItemCode());
        if(index != -1) {
            if(!getItemList()[index].getName().equalsIgnoreCase(item.getName()))
                return false;
            getQuantityList()[index] += quantity;
            getItemList()[index].setRate(item.getRate());

        }
        else {
            getItemList()[size] = item;
            getQuantityList()[size] = quantity;
            ++size;
        }
        return true;
    }

    public boolean addItem(int code, String name, double rate, int quantity) {
        Item i = new Item(code, name, rate);
        return addItem(i, quantity);
    }

    protected boolean _updateQuantity(int index, int quantity) {
        if(index >= getCapacity())
            return false;
        if(quantity < 0)
            return false;
        getQuantityList()[index] += quantity;
        return true;
    }

    public boolean updateQuantity(int code, int quantity) {
        int index = searchItem(code);
        if(index == -1)
            return false;
        return _updateQuantity(index, quantity);
    }

    public boolean updateQuantity(Item item, int quantity) {
        return addItem(item, quantity);
    }

    public boolean updateRate(int code, double rate) {
        int index = searchItem(code);
        if(index == -1)
            return false;
        getItemList()[index].setRate(rate);
        return true;
    }

    public double issueItem(int code, int quantity) {
        if(quantity < 0)
            return -1;
        int index = searchItem(code);
        if(index == -1)
            return -1;
        if(getQuantityList()[index] < quantity)
            return -1;
        getQuantityList()[index] -= quantity;
        return (getItemList()[index].getRate() * quantity);
    }

    public String toStringItem(int code) {
        int index = searchItem(code);
        if(index == -1) {
            System.out.println("Code error!");
            return "";
        }
        else {
            StringBuilder sB = new StringBuilder(String.format("%-40s%-15s%-15s%-15s\n", "Name", "Item Code", "Rate", "Quantity"));
            sB.append(getItemList()[index].toString());
            sB.append(String.format("%-15s\n", getQuantityList()[index]));
            return sB.toString();
        }
    }

    public String toString() {
        StringBuilder sB = new StringBuilder(String.format("%-40s%-15s%-15s%-15s\n", "Name", "Item Code", "Rate", "Quantity"));
        for(int i = 0; i < getSize(); ++i) {
            sB.append(getItemList()[i].toString());
            sB.append(String.format("%-15s\n", getQuantityList()[i]));
        }
        return sB.toString();
    }

    public String toStringRateGreaterThan(double rate) {
        StringBuilder sB = new StringBuilder(String.format("%-40s%-15s%-15s%-15s\n", "Name", "Item Code", "Rate", "Quantity"));
        for(int i = 0; i < getSize(); ++i) {
            if(getItemList()[i].getRate() > rate) {
                sB.append(getItemList()[i].toString());
                sB.append(String.format("%-15s\n", getQuantityList()[i]));
            }
        }
        return sB.toString();
    }
}

class TestItem
{
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("1. Add Item");
        System.out.println("2. Update Quantity");
        System.out.println("3. Update Rate");
        System.out.println("4. Issue Item");
        System.out.println("5. Get Item details");
        System.out.println("6. Items with price greater than");
        System.out.println("7. Get all item details");
        System.out.println("8. Exit");
        ItemList il = new ItemList(100);
        while(true) {
            System.out.print("Enter choice: ");
            int choice = Integer.parseInt(bf.readLine());
            switch(choice) {
                case 1:
                    {
                        System.out.print("Item Code: ");
                        int code = Integer.parseInt(bf.readLine());
                        System.out.print("Name: ");
                        String name = bf.readLine();
                        System.out.print("Rate: ");
                        double rate = Double.parseDouble(bf.readLine());
                        System.out.print("Quantity: ");
                        int quantity = Integer.parseInt(bf.readLine());
                        if(il.addItem(code, name, rate, quantity))
                            System.out.println("Successful\n");
                        else
                            System.out.println("Failed\n");
                    }
                    break;
                case 2:
                    {
                        System.out.print("Enter item code: ");
                        int code = Integer.parseInt(bf.readLine());
                        System.out.print("Enter Quantity: ");
                        int quantity = Integer.parseInt(bf.readLine());
                        if(il.updateQuantity(code, quantity))
                            System.out.println("Successful\n");
                        else
                            System.out.println("Failed\n");
                    }
                    break;
                case 3:
                    {
                        System.out.print("Enter item code: ");
                        int code = Integer.parseInt(bf.readLine());
                        System.out.print("Enter Rate: ");
                        double rate = Double.parseDouble(bf.readLine());
                        if(il.updateRate(code, rate))
                            System.out.println("Successful\n");
                        else
                            System.out.println("Failed\n");
                    }
                    break;
                case 4:
                    {
                        System.out.print("Enter item code: ");
                        int code = Integer.parseInt(bf.readLine());
                        System.out.print("Enter Quantity: ");
                        int quantity = Integer.parseInt(bf.readLine());
                        double cost = il.issueItem(code, quantity);
                        if(cost >= 0)
                            System.out.println("Cost: " + cost);
                        else
                            System.out.println("Failed\n");
                    }
                    break;
                case 5:
                    {
                        System.out.print("Enter item code: ");
                        int code = Integer.parseInt(bf.readLine());
                        System.out.println(il.toStringItem(code));
                    }
                    break;
                case 6:
                    {
                        System.out.print("Enter Rate: ");
                        double rate = Double.parseDouble(bf.readLine());
                        System.out.println(il.toStringRateGreaterThan(rate));
                    }
                    break;
                case 7:
                    {
                        System.out.println(il);
                    }
                    break;
                case 8:
                    break;
                default:
                    System.out.println("Invalid Entry!");
            }
            if(choice == 8)
                break;
        }
    }
}