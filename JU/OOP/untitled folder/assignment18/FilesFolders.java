package java_assignments.assignment18;

import java.io.*;
import java.util.*;

public class FilesFolders{

    public static void main(String args[]) throws IOException{

        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter directory name: ");
        String directoryName=br.readLine();
        System.out.println();
        File directory = new File(directoryName);
        File files[];
        files = directory.listFiles();

        if(args.length==0){
            Arrays.sort(files, new Comparator<File>(){
                public int compare(File f1, File f2){
                    return (f1.getName().compareTo(f2.getName()));
                }
            });
            System.out.println("SORTED BY NAME\n");
                for(File x: files){
                    System.out.println(x.getName());
                }
        }
        else if(args.length==1){
            if(args[0].equals("-d")){
                Arrays.sort(files, new Comparator<File>(){
                    public int compare(File f1, File f2){
                        return (int)(Long.valueOf(f2.lastModified()).compareTo(Long.valueOf(f1.lastModified())));
                    }
                });
                System.out.println("SORTED BY LAST DATE MODIFIED: form most recent to least\n");
                for(File x: files){
                    System.out.println(x.getName());
                }
            }
            else if(args[0].equals("-s")){
                Arrays.sort(files, new Comparator<File>(){
                    public int compare(File f1, File f2){
                        return (int)((Long.valueOf(f1.getTotalSpace())).compareTo(Long.valueOf(f2.getTotalSpace())));
                    }
                });
                System.out.println("SORTED BY SIZE: form largest to smallest\n");
                for(File x: files){
                    System.out.println(x.getName());
                }
            }
            else
                System.out.println("Invalid Input! Aborting...");
        }
    }
}


