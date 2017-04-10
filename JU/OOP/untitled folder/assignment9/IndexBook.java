import java.io.*;
import java.util.*;

public class IndexBook{
	static String getWord(String word){
		String new_word="";
		for(int i=0;i<word.length();i++){
			if(!(word.charAt(i)=='\''|| word.charAt(i)==']'|| word.charAt(i)=='['|| word.charAt(i)=='}'|| word.charAt(i)=='{'|| word.charAt(i)=='('|| word.charAt(i)==')'|| word.charAt(i)=='!'|| word.charAt(i)=='?'|| word.charAt(i)=='-'|| word.charAt(i)==','|| word.charAt(i)=='.'|| word.charAt(i)==':'|| word.charAt(i)==';' || word.charAt(i)=='\t' || word.charAt(i)==' '))
				new_word=new_word+word.charAt(i);
		}
		return new_word;
	}

	public static void main(String args[]) throws IOException{
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		System.out.print("Enter path of text file: ");
		String path=br.readLine();
		int pos=1;
		HashMap<String,ArrayList<Integer>> index = new HashMap<>();
    	br = new BufferedReader(new FileReader(path));
		String line,new_word;
		ArrayList<Integer> temp;
		while((line=br.readLine())!=null){
			for(String word: line.split(" ")){
				new_word=getWord(word).toUpperCase();
				if(new_word!=""){
					if(index.containsKey(new_word)){
						temp=index.get(new_word);
						if(!temp.contains(pos))
							temp.add(pos);
					}
					else{
						temp=new ArrayList<Integer>();
						temp.add(pos);
						index.put(new_word,temp);
					}
				}
			}
			pos++;
		}

		System.out.println("\nINDEX OF WORDS AND CORRESPONDING LINE NUMBERS...\n");
		for (String key:index.keySet()) {
    		System.out.print(key+" : ");
    		for (int i=0;i<index.get(key).size();i++)
    			System.out.print(index.get(key).get(i)+" ");
    		System.out.println();
		}
	}
}
