import java.io.*;
import java.util.Scanner;
public class Example11_05
{
	public static void main(String[] args)
	{
		byte[] b=new byte[1024];//�����ֽڻ�����
		int n=-1;
		System.out.println("������Ҫ��ȡ���ļ���:(���磺d:\\hello.txt)");
		Scanner scanner =new Scanner(System.in);
		String str=scanner.nextLine();//��ȡҪ��ȡ���ļ���
		
		try
		{
			FileInputStream in=new FileInputStream(str);//�����ֽ�������
			while((n=in.read(b,0,1024))!=-1)
			{//��ȡ�ļ����ݵ�������������ʾ
				String s=new String (b,0,n);
				System.out.println(s);
			}
			in.close();//��ȡ�ļ��������ر��ļ�
			}
		catch(IOException e)
		{
			System.out.println("�ļ���ȡʧ��");
		}
	}
}
