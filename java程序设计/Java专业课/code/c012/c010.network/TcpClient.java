package C010_NetWork;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;

/**
 * project_name: Java_Ex
 *
 * package_name: C010_NetWork 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-1 ÏÂÎç9:21:07 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: TcpClient.java  
 *
 * Description:  
 *
 */
public class TcpClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
				
		try {
			clientSocket = new Socket(serverAddress, serverPort);
			in = new BufferedReader(new InputStreamReader(
					clientSocket.getInputStream()));
			out = new PrintWriter(clientSocket.getOutputStream());
			out.println("User"+Math.abs(random.nextInt())%100+"@ is login.");
			out.flush();
			
			new Thread(new Runnable() {				
				@Override
				public void run() {
					// TODO Auto-generated method stub
					while (true) {
						try {
							Thread.sleep(100);
						} catch (InterruptedException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
						try {
							System.out.println(in.readLine());
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				}
			}).start();
			while (true) {
				Scanner scanner = new Scanner(System.in);
				cmd = scanner.nextLine();
				out.println(cmd);
				out.flush();
				if ("quit".equals(cmd)){
					System.exit(0);
				}
			}
		} catch (Exception e) {
		}
	}
	
	static Socket clientSocket;
	static String serverAddress = "127.0.0.1";
	static int serverPort = 9998;
	static BufferedReader in;
	static PrintWriter out;
	static Random random = new Random();
	static String cmd;
	
}


 