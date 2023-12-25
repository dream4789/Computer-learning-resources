import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
public class Example13_02_Client
{
	public static void main(String[] args) 
	{
		Socket client_socket=null;
		DataInputStream in=null;
		DataOutputStream out=null;
		String ip="127.0.0.1";//服务器IP
		int port=8000;//服务器端口
		try
		{
			client_socket=new Socket(ip,port);//与服务器建立连接
			in=new DataInputStream(client_socket.getInputStream());//创建输入流
			out=new DataOutputStream(client_socket.getOutputStream());//创建输出流
			out.writeUTF("你好，我是客户机");//向服务器端发送信息
			System.out.println("客户机启动，向服务器发送信息：你好，我是客户机");
			String str=in.readUTF();//等待读取服务器端响应的信息，进入阻塞状态
			System.out.println("服务器端的响应信息："+str);
		}
		catch (Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			try//关闭网络连接
			{
				in.close();
				out.close();
				client_socket.close();
			}
			catch(Exception e){}
		}
	}
}
