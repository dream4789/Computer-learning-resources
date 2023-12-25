package ch7;
import java.io.*;
import java.util.Scanner;
public class Example7_04  
{  
	public static void main (String[] args)  
	{  
		try  
		{  
			System.out.print("�������ļ�����");  
			Scanner reader=new Scanner(System.in);
			String filename=reader.nextLine();
			
			FileInputStream fileIn=new FileInputStream(filename);  
			StreamTokenizer in=new StreamTokenizer(fileIn);  
			in.ordinaryChar(46); // .Ϊ��ͨ�ַ�
			in.ordinaryChar(34); // ��Ϊ��ͨ�ַ�
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
			
			System.out.println("�������Ϊ��"+count);
			System.out.println("������Ϊ��"+wordCount);
			System.out.println("������Ϊ��"+numCount);
			System.out.println("��������Ϊ��"+punctionCount++);
		}
		catch (IOException e)
		{  
			System.out.println(e.getMessage());
		}
	}
}
