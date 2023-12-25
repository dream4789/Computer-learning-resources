import java.io.*;
import java.util.*;

public class Example11_04
{
	public static void main(String[] args)
	{
		File file = new File("d:\\student.txt");//创建文件对象
		double score,total=0;
		int num=0;
		try
		{
			Scanner reader=new Scanner(file);
			reader.useDelimiter("[^0-9.]+");//设置非数字作为分隔符
			
			while(reader.hasNextDouble())//是否还有成绩？
			{
				score=reader.nextDouble();//有，读出并相加
				total=total+score;
				num++;
			}
			System.out.println("平均成绩："+total/num);
		}
		catch(Exception e)
		{}
	}
}
