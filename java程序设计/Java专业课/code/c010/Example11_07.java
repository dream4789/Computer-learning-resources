import java.io.*;
import java.util.Scanner;
public class Example11_07
{
public static void main(String[] args) throws IOException
	{
		Scanner scanner=new Scanner(System.in);
		System.out.println("������Դ�ļ�����Ŀ���ļ������м��ÿո�ָ�");
		String s=scanner.next();//��ȡԴ�ļ���
		String d=scanner.next();//��ȡĿ���ļ���
		File file1=new File(s);//����Դ�ļ�����
		File file2=new File(d);//����Ŀ���ļ�����
		 
		if(!file1.exists())
		{
			System.out.println("�����Ƶ��ļ�������");
			System.exit(1);
		}
		
		InputStream input=new FileInputStream(file1);//����Դ�ļ���
		OutputStream output=new FileOutputStream(file2);//����Ŀ���ļ���
		if((input!=null)&&(output!=null))
		{
			int temp=0;
			while((temp=input.read())!=(-1))//����һ���ַ�
				output.write(temp);//���Ƶ����ļ���
		}
		input.close();//�ر�Դ�ļ���
		output.close();//�ر�Ŀ���ļ���
		System.out.println("�ļ����Ƴɹ���");
	}
}
