import java.io.*;
import java.util.Scanner;
public class Example11_01
{
	public static void main(String[] args)
	{
		Scanner scanner=new Scanner(System.in);
		System.out.println("�������ļ��������磺e:\\example.txt");
		String s=scanner.nextLine();
		File file=new File(s);
				System.out.println("�ļ�����"+file.getName());
		System.out.println("�ļ���СΪ��"+file.length()+"�ֽ�");
		System.out.println("�ļ�����·��Ϊ��"+file.getAbsolutePath());
				if (file.isHidden())
		{
			System.out.println("���ļ���һ�������ļ�");
		}
		else
		{
			System.out.println("���ļ�����һ�������ļ�");
		}
		if (!file.exists())
		{
			System.out.println("���ļ�������");
			try
			{
				file.createNewFile();
				System.out.println("���ļ������ɹ�");
			}
			catch(IOException e){}
		}
	}
}
