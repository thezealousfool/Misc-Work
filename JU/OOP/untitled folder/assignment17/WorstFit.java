package java_assignments.assignment17;

import java.io.*;
import java.util.*;
import java.text.*;

class Folders{
	ArrayList<File> file;
	int index;
	static int count=0;

	Folders(){
		file=new ArrayList<>();
		index=count;
		count++;
	}

	long getSize(){
		long sum=0;
		for(File f: file)
			sum=sum+f.length();
		return sum;
	}
	void add(File f){
		file.add(f);
	}
}

public class WorstFit{
	public static void main(String args[]) throws Exception{
		ArrayList<File> files=new ArrayList<File>();
		int len=args.length;
		SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
		String date_limit="01/01/1990 00:00:00";
		long limit = (dateFormat.parse(date_limit)).getTime();
		for(int i=0;i<len;i++)
			files.add(new File(args[i]));
		//files.get(4).setLastModified(limit-1);
		for(int i=0;i<files.size();i++){
			long last_modified=files.get(i).lastModified();
			if(last_modified<limit){
				System.out.println("\n"+files.get(i).getName()+" is ignored as it has not been modified after 1st January 1990\n");
				files.remove(i);
			}
			else
				files.get(i).setLastModified(new Date().getTime());
		}
		ArrayList<Folders> folders=new ArrayList<>();
		int folder_index=0;
		long total_sum=files.get(0).length();
		folders.add(new Folders());
		folders.get(0).add(files.get(0));
		files.remove(0);
		for(int i=0;i<files.size();i++){
			long min=100000000;
			int min_index=0;
			for(int j=folder_index;j>=0;j--){
				long sum=folders.get(j).getSize();
				if(sum<min){
					min=sum;
					min_index=j;
				}
			}
			if((files.get(i).length()+min)<=1024){
				folders.get(min_index).add(files.get(i));
			}
			else{
				folders.add(new Folders());
				folder_index++;
				folders.get(folder_index).add(files.get(i));
			}
			total_sum+=files.get(i).length();
		}

		System.out.println("\nFile sizes sum= "+total_sum/1024+" KB\nTotal folders= "+(folder_index+1)+"\n");
		
		Collections.sort(folders, new sortBySize());
		System.out.println("FOLDERS\t\tOCCUPIED\tFREE SPACE\tFILES\n");
		for(int i=0;i<=folder_index;i++){
			System.out.print("Folder "+(folders.get(i).index+1)+"\t"+folders.get(i).getSize()+" KB\t\t"+(1024-folders.get(i).getSize())+" KB\t\t");
			for(int j=0;j<folders.get(i).file.size();j++)
				System.out.print(folders.get(i).file.get(j).getName()+"  ");
			System.out.println();
		}
	}
}

class sortBySize implements Comparator<Folders>{
	public int compare(Folders f1, Folders f2){
		return (int)(f1.getSize()-f2.getSize());
	}
}