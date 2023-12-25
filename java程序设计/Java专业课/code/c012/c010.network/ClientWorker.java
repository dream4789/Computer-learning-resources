package C010_NetWork;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

/**
 * project_name: Java_Ex
 *
 * package_name: C010_NetWork 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-1 下午8:58:16 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ClientWorker.java  
 *
 * Description:  
 *
 */
public class ClientWorker implements Runnable{

	public ClientWorker(Socket s) throws IOException {
		socket = s;
		in = new BufferedReader(new InputStreamReader(s.getInputStream()));
		//out = new PrintWriter(s.getOutputStream());
	}
		
	@Override
	public void run() {
		while (userName == null) {
			try {
				String inMsg = in.readLine();
				userName= inMsg.split("@")[0];
				ServerWorker.sendAllClients(inMsg);
			} catch (IOException ee) {
				ee.printStackTrace();
			}
		}
		while (true) {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			try {
				String line = in.readLine();
				/** 处理退出事件(读取信息) */
				if (line.equals("quit")) {
					ServerWorker.sendAllClients(userName+" has quit." );
					ServerWorker.deleteConnection(socket, this);
					return;
				}else{
					ServerWorker.sendAllClients(userName+" says: "+line);
				}
			}catch(Exception e){
				System.out.println(e.toString());
				try {
					socket.close();
				} catch (IOException e2) {
				}
				return;
			}
		}
	}
	
	private Socket socket;
	private BufferedReader in;
	//private PrintWriter out;
	private String userName;

}


 