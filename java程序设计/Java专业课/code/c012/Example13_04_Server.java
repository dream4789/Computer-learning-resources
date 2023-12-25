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
				System.out.println("服务器启动！");
			}
			catch(IOException e1) 
			{ 
				System.out.println("正在监听"); //ServerSocket对象不能重复创建
			} 
			
			try
			{  
				System.out.println("等待客户请求");
				socket=server_socket.accept();
				System.out.println("客户的地址:"+
socket.getInetAddress()+":"+socket.getPort());
			} 
			catch (IOException e) 
			{
				System.out.println("正在等待客户");
			}
			
			if(socket!=null) 
			{ 
				new Example13_04_LogicThread(socket);//创建一个新线程进行处理  
			}
		} 
	}
}
