import java.util.Scanner;
import java.io.*;
public class Example11_09
{
	public static void main(String[] args)
	{
		File file;
		FileReader fin;
		FileWriter fout;
		BufferedReader bin;
		BufferedWriter bout;
		Scanner scanner = new Scanner(System.in);
		System.out.println("�������ļ���������d:\\hello.txt");
		String filename = scanner.nextLine();
	
		try
		{
			file = new File(filename);//�����ļ�����
			if (!file.exists())
			{
				file.createNewFile();//�������ļ�
				fout = new FileWriter(file);//�����ļ����������
			} 
			else
				fout = new FileWriter(file, true);//����׷�����ݵ��ļ����������
	
			fin = new FileReader(file);//�����ļ�������
			bin = new BufferedReader(fin);//��������������
			bout = new BufferedWriter(fout);//�������������
			
			System.out.println("���������ݣ����һ��Ϊ�ַ���0��������");
			String str = scanner.nextLine();//�Ӽ��̶�ȡ�������ַ���
			while (!str.equals("0"))
			{
				bout.write(str);//����ַ�������
				bout.newLine();//������з�
				str = scanner.nextLine();//����һ��
			}
			bout.flush();//ˢ�������
			bout.close();//�رջ��������
			fout.close();//�ر��ļ������
			System.out.println("�ļ�д����ϣ�");	
			//���½��ļ�������ʾ����
			System.out.println("�ļ�" + filename + "�������ǣ�");
			while ((str = bin.readLine()) != null)
				System.out.println(str);//��ȡ�ļ����ݲ���ʾ
	
			bin.close();//�رջ���������
			fin.close();//�ر��ļ�������
		}
		catch (IOException e)
		{e.printStackTrace();}
	}
}
