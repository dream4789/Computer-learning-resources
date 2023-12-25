package C010_NetWork;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;


/**
 * project_name: Java_Ex
 *
 * package_name: C010_NetWork 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-1 ÏÂÎç8:56:08 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ServerWorker.java  
 *
 * Description:  
 *
 */
public class ServerWorker {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int port = DEFAULT_PORT;
		try {
			serverSocket = new ServerSocket(port);
			System.out.println("Server is started");
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		}
		while (true) {
			try {
				Socket socket = serverSocket.accept();
				ClientWorker cw = new ClientWorker(socket);
				Thread ct = new Thread(cw);
				ct.start();
				addConnection(socket, cw);
			} catch (IOException e) {
				System.err.println(e);
			}
		}
	}
	
	public static void addConnection(Socket s, ClientWorker cw) {
		if (connections == null) {
			connections = new ArrayList<Socket>();
		}
		connections.add(s);

		if (clients == null) {
			clients = new ArrayList<ClientWorker>();
		}
		clients.add(cw);
	}
	
	public static void deleteConnection(Socket s, ClientWorker cw)
			throws IOException {
		if (connections != null) {
			connections.remove(s);
			s.close();
		}
		if (clients != null) {
			clients.remove(cw);
		}
	}

	public static List<ClientWorker> getClients() {
		return clients;
	}
	
	public static void sendAllClients(String str) {
		if (connections != null) {
			for (Socket socket : connections) {
				try {
					PrintWriter pw = new PrintWriter(socket.getOutputStream());
					pw.println(str);
					pw.flush();
				} catch (IOException ex) {
					ex.printStackTrace();
				}
			}
		}
		System.out.println(str);
	}
	
	private static final int DEFAULT_PORT = 9998;
	private static ServerSocket serverSocket;
	private static List<Socket> connections;// Á¬½Ó
	private static List<ClientWorker> clients;

}


 