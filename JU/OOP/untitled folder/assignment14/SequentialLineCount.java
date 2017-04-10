package java_assignments.assignment14;

import java.io.*;

class FileLineCount{
    File files[];
    int no_of_files;
    static int index=0;

    FileLineCount(File f[]){
        int num=f.length;
        files=new File[num];
        for(int i=0;i<num;i++)
            files[i]=f[i];
    }

    synchronized public void countLines() throws IOException {
        LineNumberReader reader = null;
        try {
            reader = new LineNumberReader(new FileReader(files[index]));
            while ((reader.readLine()) != null);
            System.out.println("Number of lines in "+files[index].getName()+" is: "+reader.getLineNumber());
            index++;
        }
        catch (Exception ex) {
            System.out.println("Exception caught in file: "+files[index].getName());
        }
        finally { 
            if(reader != null) 
                reader.close();
        }
    }
}

class LineCounter implements Runnable{

    FileLineCount f;
    public LineCounter(FileLineCount f){
        this.f=f;
    }

    public void run(){
        try{
            f.countLines();
        }
        catch(IOException e){
            System.out.println("Exception caught...");
        }
    }
}

public class SequentialLineCount{
    public static void main(String args[])throws IOException,InterruptedException{
        long t1=System.currentTimeMillis();
        Thread th[]=new Thread[args.length];
        File files[]=new File[args.length];
        for(String filename: args)
            files[i]=new File(filename);
        FileLineCount fob=new FileLineCount(files);
        for(int i=0;i<args.length;i++){
            LineCounter lob=new LineCounter(fob);
            Thread t=new Thread(lob,"Line counter "+(i+1));
            th[i]=t;
            t.start();
        }
        for(int i=0;i<args.length;i++)
            th[i].join();
        long t2=System.currentTimeMillis();
        System.out.println("Time in milliseconds: "+(t2-t1));
    }
}
