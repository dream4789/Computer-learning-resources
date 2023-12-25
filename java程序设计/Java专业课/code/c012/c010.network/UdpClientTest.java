package C010_NetWork;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 * project_name: Java_Ex
 *
 * package_name: C010_NetWork 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-2 ÉÏÎç9:17:09 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: UdpClientTest.java  
 *
 * Description:  
 *
 */
public class UdpClientTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		
        InetAddress address = InetAddress.getByName("localhost");
        int port = 9999;
        byte[] data = "username£ºadmin;pwd£º123".getBytes();        
        DatagramPacket packet = new DatagramPacket(data, data.length, address, port);        
        DatagramSocket socket = new DatagramSocket();
        socket.send(packet);
        
        byte[] data2 = new byte[1024];
        DatagramPacket packet2 = new DatagramPacket(data2, data2.length);
        socket.receive(packet2);
        String reply = new String(data2, 0, packet2.getLength());
        System.out.println("UDP SERVER SAYS£º" + reply);        
        socket.close();
	}

}


 