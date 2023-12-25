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
 * created Time: 2018-1-1 下午8:24:46 
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
			s = ss.accept();// 客户端连上后返回Socket，监听端口
			System.out.println("Client is online...");
			OutputStream os = s.getOutputStream();
			PrintWriter pw = new PrintWriter(os);
			pw.println("欢迎欢迎！");// 要换行，否则不能读取
			pw.flush();// 从内存输出去
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


 