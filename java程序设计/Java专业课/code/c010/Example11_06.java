import java.io.*;
import java.util.Scanner;
public class Example11_06
{
	public static void main(String[] args)
	{
		String content;//������ַ���
		byte[] b;//����ֽ���
		FileOutputStream out;//�ļ������
		Scanner scanner = new Scanner(System.in);
		System.out.println("�������ļ����������磬d:\\hello.txt��");
		String filename=scanner.nextLine();
		File file = new File(filename);//�����ļ�����
	
		if (!file.exists())
		{//�ж��ļ��Ƿ����
			System.out.println("�ļ������ڣ��Ƿ񴴽���(y/n)");
			String f =scanner.nextLine();
			if (f.equalsIgnoreCase("n"))
				System.exit(0);//���������˳�
			else
			{
				try
				{
					file.createNewFile();//�������ļ�
				}
				catch(IOException e)
				{
					System.out.println("����ʧ��");
					System.exit(0);
				}
			}
		}
		
		try
		{//���ļ���д����
			content="Hello";
			b=content.getBytes();
			out = new FileOutputStream(file);//�����ļ������
			out.write(b);//���д����
			out.close();//�ر������
			System.out.println("�ļ�д�����ɹ���");
		}
		catch(IOException e)
		{e.getMessage();}
		
		try
		{//���ļ���׷������
			System.out.println("������׷�ӵ����ݣ�");
			content = scanner.nextLine();
			b=content.getBytes();
			out = new FileOutputStream(file,true);//������׷�����ݵ������
			out.write(b);//���׷��д����
			out.close();//�ر������
			System.out.println("�ļ�׷��д�����ɹ���");
			scanner.close();
		}
		catch(IOException e)
		{e.getMessage();}
	}
}
