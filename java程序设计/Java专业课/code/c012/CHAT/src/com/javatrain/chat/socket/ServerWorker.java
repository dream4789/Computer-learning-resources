package com.javatrain.chat.socket;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

import com.javatrain.chat.util.ResourceBundler;

public class ServerWorker {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int port = DEFAULT_PORT;
		try {
			serverSocket = new ServerSocket(port);
			System.out.println(ResourceBundler.getString("Server.Start.Info"));
		} catch (IOException e) {
			System.out.println(ResourceBundler
					.getString("Server.Start.Exception.Info"));
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

	public static boolean sendOneClient(String name, String msg) {
		if (clients != null) {
			for (ClientWorker cw : clients) {
				if ((cw.getUserName()).equals(name)) {
					try {
						PrintWriter pw = new PrintWriter((cw.getSocket())
								.getOutputStream());
						pw.println(msg);
						pw.flush();
						return true;
					} catch (IOException ioe) {
						ioe.printStackTrace();
					}
				}
			}
		}
		return false;
	}

	public static boolean sendOneClient(String from,String to,String id, ResultSet rs) {
		if (clients != null) {
			for (ClientWorker cw : clients) {
				if ((cw.getUserName()).equals(to)) {
					try {
						PrintWriter pw = new PrintWriter((cw.getSocket())
								.getOutputStream());
						StringBuffer msg = new StringBuffer("Command&Nosql&"+from+" 和 "+ to+" [之间无无聊天记录!] "+"&"+id);
						System.out.println(to);
						rs.last();
						int row = rs.getRow();
						if(row == 0){
							pw.println(msg.toString());
						    pw.flush();
						}else{					
							try {
								rs.beforeFirst();
								while(rs.next()){
									msg.delete(0, msg.length());
									msg.append("Command&sql&"); 
									msg.append(rs.getString(2)+"&"); 
									msg.append(rs.getString(3)+"&"); 
									msg.append(rs.getString(4)+"&"); 
									msg.append(rs.getString(5)+"&"+id); 
//System.out.println(msg.toString());
									pw.println(msg.toString());
								    pw.flush();
								}
							} catch (SQLException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}finally{
								try {
									rs.close();
								} catch (SQLException e) {
									// TODO Auto-generated catch block
									e.printStackTrace();
								}
							}
							
							
							
						}
						
						return true;
					} catch (IOException ioe) {
						ioe.printStackTrace();
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}
		return false;
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

	// 获取与数据操作对象
	public static DbUtil getDbUtil() {
		return DbUtil.getInstance();
	}
	//生成唯一的用户ID
	public static int produceUserID() {
		int id = 0;
		do {
			id = (int) (Math.random() * maxIDVaule + minIDVaule);
		} while (userID.contains(id));

		return id;

	}
    private static HashSet<Integer> userID = new HashSet<Integer>();
	private static final int maxIDVaule = 1000;
	private static final int minIDVaule = 0;
    private static final int DEFAULT_PORT = 9998;
	private static ServerSocket serverSocket;
	private static List<Socket> connections;// 连接
	private static List<ClientWorker> clients;
}
