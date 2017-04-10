class ReadWritePermission{

    int readers=0;
    int writers=0;
    int write_requests=0;

    synchronized void getReadPermission(){
        while(writers>0 || write_requests>0){
            try{
                wait();
            }
            catch(InterruptedException e){
                System.out.println("InterruptedException caught: in getReadPermission()");
            }
        }
        readers++;
    }

    synchronized void releaseReadPermission(){
        readers--;
        notifyAll();
    }

    synchronized void getWritePermission(){
        write_requests++;
        while(readers>0 || writers>0){
            try{
                wait();
            }
            catch(InterruptedException e){
                System.out.println("InterruptedException caught: in getWritePermission()");
            }
        }

        write_requests--;
        writers++;
    }

    synchronized void releaseWritePermission(){
        writers--;
        notifyAll();
    }
}

class Data{

    int x=0;

    synchronized void get(){
        System.out.println("Reading "+x);
    }

    synchronized void set(int k){
        x=k;
        System.out.println("Writing "+x);
    }
}

class Reader implements Runnable{

    Data d;
    ReadWritePermission p;

    Reader(Data d, ReadWritePermission p){
        this.d=d;
        this.p=p;
    }

    public void run(){
        p.getReadPermission();
        d.get();
        p.releaseReadPermission();
    }
}

class Writer implements Runnable{

    Data d;
    ReadWritePermission p;

    Writer(Data d, ReadWritePermission p){
        this.d=d;
        this.p=p;
    }

    public void run(){
        p.getWritePermission();
        d.set((d.x)+1);
        p.releaseWritePermission();
    }
}

public class ReadWriteDemo2{
    public static void main(String args[]){
        Data d=new Data();
        ReadWritePermission p=new ReadWritePermission();
        Reader rd=new Reader(d,p);
        Writer wt=new Writer(d,p);
        Thread read_t1=new Thread(rd,"Reader1");
        Thread read_t2=new Thread(rd,"Reader2");
        Thread read_t3=new Thread(rd,"Reader3");
        Thread read_t4=new Thread(rd,"Reader4");
        Thread read_t5=new Thread(rd,"Reader5");
        Thread write_t1=new Thread(wt,"Writer1");
        Thread write_t2=new Thread(wt,"Writer2");
        Thread write_t3=new Thread(wt,"Writer3");
        Thread write_t4=new Thread(wt,"Writer4");
        Thread write_t5=new Thread(wt,"Writer5");
        Thread write_t6=new Thread(wt,"Writer6");
        read_t1.start();
        write_t1.start();
        read_t2.start();
        write_t2.start();
        read_t3.start();
        write_t3.start();
        read_t4.start();
        write_t4.start();
        read_t5.start();
        write_t5.start();
        write_t6.start();
    }
}
