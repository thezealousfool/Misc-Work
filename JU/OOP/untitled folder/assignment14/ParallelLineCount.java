package java_assignments.assignment14;

import java.io.*;

class FileLineCount{
    File file;

    FileLineCount(File file){
        this.file=file;
    }

    public void countLines() throws IOException{
        LineNumberReader reader = null;
        try {
            reader = new LineNumberReader(new FileReader(file));
            while ((reader.readLine()) != null);
            System.out.println("Number of lines in "+file.getName()+" is: "+reader.getLineNumber());
        }
        catch (Exception ex) {
            System.out.println("Exception caught in file: "+file.getName());
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
            System.out.println("In run() method of "+f.file.getName());
            f.countLines();
        }
        catch(IOException e){
            System.out.println("Exception caused by file: "+f.file.getName());
        }
    }
}

public class ParallelLineCount{
    public static void main(String args[]) throws IOException,InterruptedException{
        long t1=System.currentTimeMillis();
        Thread th[]=new Thread[args.length];
        for(int i=0;i<args.length;i++){
            FileLineCount fob=new FileLineCount(new File(args[i]));
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

