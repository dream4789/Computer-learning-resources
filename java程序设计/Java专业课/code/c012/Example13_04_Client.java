import java.io.*;
import java.net.*;
import java.util.*;
public class Example13_04_Client
{
	public static void main(String[] args)
	{
		Scanner scanner = new Scanner(System.in);
		String input=null;
		Socket socket=null;
		DataInputStream in=null;
		DataOutputStream out=null;
		String serverIP="127.0.0.1"; //��������ַ
		int port=8000;//�������˿�
		
		try
		{  
			socket=new Socket(serverIP,port);//���ӷ�����
			in=new DataInputStream(socket.getInputStream());//����������
			out=new DataOutputStream(socket.getOutputStream());//���������
			System.out.println("������һ��������������������ʽ��");
			
			while(scanner.hasNext())
			{
				input=scanner.nextLine();//�Ӽ�������һ�������������������ʽ
				if (!input.equals("0"))
				{
					out.writeUTF(input);//��������˷�����������
					String result=in.readUTF();//�ȴ���ȡ������
					System.out.println("���������صļ�������"+result);
					System.out.println("������һ��������������������ʽ(����0�˳�)��");
				}
				else 
					break;//�������
			}
		}
		catch(Exception e)
		{
			System.out.println("������������ж�");
		}
		finally
		{
			try//�ر���������
			{
				in.close();
				out.close();
				socket.close();
				System.out.println("���ӽ���");
			}
			catch(Exception e){}
		}
	}
}
