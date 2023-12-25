import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
public class Example13_05_Server_UDP
{
	public static void main(String[] args)
	{
		DatagramSocket socket=null;
		DatagramPacket packet_send=null;
		DatagramPacket packet_receive=null;
		int port=8158;//服务器监听端口
		try
		{
			socket=new DatagramSocket(port);//创建连接对象
			System.out.println("服务器启动成功！");
			byte [] r=new byte[1024];//创建缓存数组
			packet_receive=new DatagramPacket(r,r.length);//创建数据包对象
			socket.receive(packet_receive);//接收数据包
			InetAddress client_ip=packet_receive.getAddress();//客户机地址
			int client_port=packet_receive.getPort();//客户机端口号
			byte [] data=packet_receive.getData();//客户机字节数据
			int len=packet_receive.getLength();//数据有效长度
			String str1=new String (data,0,len);//将字节数据转换成字符串
			System.out.println("客户机"+client_ip+":"+client_port+"\n发送的信息是："+str1);
			String response="你好，我是服务器";
			byte [] s=response.getBytes();
//创建响应数据包对象
			packet_send=new DatagramPacket(s,s.length,client_ip,client_port); 
			socket.send(packet_send);//发送响应数据包
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			socket.close();
		}
	}
}
