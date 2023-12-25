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
 * created Time: 2018-1-2 ����9:02:28 
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

		// Step1.1 ������������DatagramSocket
		DatagramSocket socket;
		try {
			socket = new DatagramSocket(9999);

			// Step1.2 �������ݱ������ڽ��տͻ��˷��͵�����
			byte[] data = new byte[1024];
			DatagramPacket packet = new DatagramPacket(data, data.length);
			// Step1.3 ���տͻ��˷��͵�����
			System.out
					.println("UDP SERVER STARTED,WAITING FOR RECEIVING DATA...");
			socket.receive(packet);// ִ�е��ˣ����̻�����ֱ�����յ�����

			// Step1.4 ��ȡ����
			String info = new String(data, 0, packet.getLength());
			System.out.println("CLIENT DATA��" + info);

			// Step2.1 ����ͻ��˵ĵ�ַ���˿ںš�����
			InetAddress address = packet.getAddress();
			int port = packet.getPort();
			byte[] data2 = "��ӭ��!".getBytes();
			// Step2.2 �������ݱ���������Ӧ��������Ϣ
			DatagramPacket packet2 = new DatagramPacket(data2, data2.length,
					address, port);
			// Step2.3 ��Ӧ�ͻ���
			socket.send(packet2);
			// Step2.4 �ر���Դ
			socket.close();
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException ioe) {
		}
	}
}
 