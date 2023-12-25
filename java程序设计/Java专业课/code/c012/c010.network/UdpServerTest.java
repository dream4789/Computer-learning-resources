package C010_NetWork;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

/**
 * project_name: Java_Ex
 *
 * package_name: C010_NetWork 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-2 上午9:02:28 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: UdpServerTest.java  
 *
 * Description: Receive data from UDP Client and response to Client. 
 *
 */
public class UdpServerTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		// Step1.1 创建服务器端DatagramSocket
		DatagramSocket socket;
		try {
			socket = new DatagramSocket(9999);

			// Step1.2 创建数据报，用于接收客户端发送的数据
			byte[] data = new byte[1024];
			DatagramPacket packet = new DatagramPacket(data, data.length);
			// Step1.3 接收客户端发送的数据
			System.out
					.println("UDP SERVER STARTED,WAITING FOR RECEIVING DATA...");
			socket.receive(packet);// 执行到此，进程会阻塞直到接收到数据

			// Step1.4 读取数据
			String info = new String(data, 0, packet.getLength());
			System.out.println("CLIENT DATA：" + info);

			// Step2.1 定义客户端的地址、端口号、数据
			InetAddress address = packet.getAddress();
			int port = packet.getPort();
			byte[] data2 = "欢迎您!".getBytes();
			// Step2.2 创建数据报，包含响应的数据信息
			DatagramPacket packet2 = new DatagramPacket(data2, data2.length,
					address, port);
			// Step2.3 响应客户端
			socket.send(packet2);
			// Step2.4 关闭资源
			socket.close();
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException ioe) {
		}
	}
}
 