package C010_NetWork;

import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * project_name: Java_Ex
 *
 * package_name: C010_NetWork 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-1 ����8:24:46 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: TcpServerTest.java  
 *
 * Description:  
 *
 */
public class TcpServerTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ServerSocket ss = null;
		Socket s = null;
		System.out.println("Server is started");
		try {
			ss = new ServerSocket(10222);
			s = ss.accept();// �ͻ������Ϻ󷵻�Socket�������˿�
			System.out.println("Client is online...");
			OutputStream os = s.getOutputStream();
			PrintWriter pw = new PrintWriter(os);
			pw.println("��ӭ��ӭ��");// Ҫ���У������ܶ�ȡ
			pw.flush();// ���ڴ����ȥ
		} catch (Exception e) {
		} finally {
			if (s != null)
				try {
					s.close();
				} catch (Exception e) {
				}
			if (ss != null)
				try {
					ss.close();
				} catch (Exception e) {
				}
		}
	}
}


 