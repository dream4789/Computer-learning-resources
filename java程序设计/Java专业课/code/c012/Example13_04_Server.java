import java.io.*;
import java.net.*;
public class Example13_04_Server
{
	public static void main(String[] args) 
	{
		ServerSocket server_socket=null;
		Socket socket=null;
		int port=8000;
		
		while(true) 
		{
			try
			{  
				server_socket=new ServerSocket(port);
				System.out.println("������������");
			}
			catch(IOException e1) 
			{ 
				System.out.println("���ڼ���"); //ServerSocket�������ظ�����
			} 
			
			try
			{  
				System.out.println("�ȴ��ͻ�����");
				socket=server_socket.accept();
				System.out.println("�ͻ��ĵ�ַ:"+
socket.getInetAddress()+":"+socket.getPort());
			} 
			catch (IOException e) 
			{
				System.out.println("���ڵȴ��ͻ�");
			}
			
			if(socket!=null) 
			{ 
				new Example13_04_LogicThread(socket);//����һ�����߳̽��д���  
			}
		} 
	}
}
