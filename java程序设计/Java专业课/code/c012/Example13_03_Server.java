import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
public class Example13_03_Server
{
	public static void main(String[] args)
	{
		ServerSocket server_socket=null;
		Socket socket=null;
		DataInputStream in=null;
		DataOutputStream out=null;
		int port=8000;
		
		try
		{
			server_socket=new ServerSocket(port);//创建绑定端口的服务器端socket
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
		
		try
		{
			System.out.println("服务器启动！");
			//监听并接受到此套接字的连接。此方法在连接传入之前处于阻塞状态
socket=server_socket.accept();
			in=new DataInputStream(socket.getInputStream());//创建输入流
			out=new DataOutputStream(socket.getOutputStream());//创建输出流
			String str=in.readUTF();//从输入流读取字符串，读取结束之前处于阻塞状态
			System.out.println("客户机发送过来的信息是： "+str);
			out.writeUTF("你好，我是服务器");//向输出流写入字符串
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			try//关闭网络连接
			{
				out.close();
				in.close();
				socket.close();
				server_socket.close();
			}
			catch(Exception e){}
		}
	}
}
