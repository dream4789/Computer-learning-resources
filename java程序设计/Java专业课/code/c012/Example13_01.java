import java.net.*;
import java.io.*;
import java.util.*;
public class Example13_01//����URL����ķ���ʾ��
{	
	public static void main(String[] args) 
	{
		Scanner scanner;//����һ���������
		URL url;//����һ��URL����
		InputStream in;//����һ��������
		String addr;//URL��ַ���ַ�����ʾ
		String str;//���������ַ�����ʾ
		System.out.println("������һ��URL��ַ��");
		scanner=new Scanner(System.in);
		addr=scanner.nextLine();//�Ӽ��̶�ȡһ��URL�ַ���
		try
		{
			url=new URL(addr);//����URL����
			in=url.openStream();//����URL������������
			byte [] b=new byte[1024];
			int n=-1;
			while ((n=in.read(b))!=-1)//����ȡ�����������
			{
				str=new String(b,0,n,"UTF-8");
				System.out.print(str);
			}
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
}
