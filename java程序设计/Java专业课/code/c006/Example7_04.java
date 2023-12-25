package ch7;
import java.io.*;
import java.util.Scanner;
public class Example7_04  
{  
	public static void main (String[] args)  
	{  
		try  
		{  
			System.out.print("请输入文件名：");  
			Scanner reader=new Scanner(System.in);
			String filename=reader.nextLine();
			
			FileInputStream fileIn=new FileInputStream(filename);  
			StreamTokenizer in=new StreamTokenizer(fileIn);  
			in.ordinaryChar(46); // .为普通字符
			in.ordinaryChar(34); // “为普通字符
			int wordCount=0,numCount=0,punctionCount=0,count=0;  
			double token;
			
			while ((token=in.nextToken())!=StreamTokenizer.TT_EOF)  
			{  
				count++;
				if (token==StreamTokenizer.TT_WORD)  
					wordCount++;  
				else if (token==StreamTokenizer.TT_NUMBER)  
					numCount++;  
				else  
					punctionCount++;     
			}
			
			System.out.println("标记总数为："+count);
			System.out.println("单词数为："+wordCount);
			System.out.println("数字数为："+numCount);
			System.out.println("标点符号数为："+punctionCount++);
		}
		catch (IOException e)
		{  
			System.out.println(e.getMessage());
		}
	}
}
