import java.io.*;
import java.util.*;

public class Example11_04
{
	public static void main(String[] args)
	{
		File file = new File("d:\\student.txt");//�����ļ�����
		double score,total=0;
		int num=0;
		try
		{
			Scanner reader=new Scanner(file);
			reader.useDelimiter("[^0-9.]+");//���÷�������Ϊ�ָ���
			
			while(reader.hasNextDouble())//�Ƿ��гɼ���
			{
				score=reader.nextDouble();//�У����������
				total=total+score;
				num++;
			}
			System.out.println("ƽ���ɼ���"+total/num);
		}
		catch(Exception e)
		{}
	}
}
