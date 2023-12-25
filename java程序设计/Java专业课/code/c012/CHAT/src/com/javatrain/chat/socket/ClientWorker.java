package com.javatrain.chat.socket;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import com.javatrain.chat.util.ResourceBundler;

public class ClientWorker implements Runnable {

	public ClientWorker(Socket s) throws IOException {
		socket = s;
		in = new BufferedReader(new InputStreamReader(s.getInputStream()));
		out = new PrintWriter(s.getOutputStream());
		updateUserList();
	}

	public String getUserName() {
		return userName;
	}

	public String getSex() {
		return sex;
	}

	public String getImageName() {
		return imageName;
	}

	public int getUserID() {
		return userID;
	}

	public void setUserID(int userID) {
		this.userID = userID;
	}

	public Socket getSocket() {
		return socket;
	}

	private void updateUserList() {
		/** 发送当前在聊天室的用户到新来的用户列表中 */
		List<ClientWorker> clentWorker = ServerWorker.getClients();
		if (clentWorker != null) {
			for (ClientWorker cw : clentWorker) {
				String u_name = cw.getUserName();
				String u_sex = cw.getSex();
				String u_icon = cw.getImageName();
				String id = cw.getUserID()+"";
				System.out.println("old" + "&" + u_name + "&" + u_sex+"&"+u_icon+"&"+id);
				out.println("old" + "&" + u_name + "&" + u_sex+"&"+u_icon+"&"+id);
				out.flush();
			}
		}
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		while (userName == null) {
			try {
				String inMsg;
				userID = ServerWorker.produceUserID();
				inMsg = in.readLine()+"&"+userID;
				System.out.println(inMsg);
				ServerWorker.sendAllClients("new&" + inMsg);
				// & boy
				String[] userInfo;
				//String strss="username&sex&icon";
				userInfo = inMsg.split("&");
				userName = userInfo[0];
				sex = userInfo[1];
				imageName = userInfo[2];
				
			} catch (IOException ee) {
				ee.printStackTrace();
			}
		}

		while (true) {
			try {
				String line = in.readLine();
				/** 处理退出事件(读取信息) */
				if (line.equals("quit")) {
					ServerWorker.sendAllClients(ResourceBundler
							.getString("Server.System.Info")
							+ this.userName
							+ ResourceBundler.getString("Server.Quit.Info"));
					ServerWorker.sendAllClients("quit"+"&"+this.userName);
					
					ServerWorker.deleteConnection(socket, this);
					return;
					/** 处理刷新用户列表请求 */
				} else if (line.equals("refurbish")) {
					this.updateUserList();
					/** 一般消息 */
				} else if (line.startsWith("command")) {
					
					String sqlMsg[] = line.split("&");
					if (sqlMsg[1].equalsIgnoreCase("sql")) {
						String sql = "select * from  chatMsg   where  ("
								+ "from_User_Number='" + sqlMsg[2] + "' and "
								+ "  to_User_Number ='" + sqlMsg[3]
								+ "')  or (" + "from_User_Number='" + sqlMsg[3]
								+ "' and " + "  to_User_Number ='" + sqlMsg[2]
								+ "') order by " + sqlMsg[4];
						DbUtil dbUtil = ServerWorker.getDbUtil();
						ServerWorker.sendOneClient(sqlMsg[3], sqlMsg[2],sqlMsg[5], dbUtil
								.executeQuery(sql));
//System.out.println("  sql   " + sql);
					}
					/** 一般消息 */
				} else {
					String[] inMsg = line.split("&");
					//向数据库写聊天记录
					if (inMsg[0].compareTo("cancelsendfile") == 0) {
						ServerWorker.sendOneClient(inMsg[1], "cancelsendfile"
								+ "&" + this.userName);
					} else if (inMsg[0].compareTo("sendfile") == 0) {

						ServerWorker.sendOneClient(inMsg[1], "sendfile" + "&"
								+ this.userName + "&" + inMsg[2] + "&"
								+ inMsg[3] + "&" + inMsg[4] + "&" + inMsg[5]);
					} else if (inMsg[0].compareTo("acceptfile") == 0) {
						ServerWorker.sendOneClient(inMsg[1], inMsg[0] + "&"
								+ this.userName);
					} else if (inMsg[0].compareTo("refusefile") == 0) {
						ServerWorker.sendOneClient(inMsg[1], inMsg[0] + "&"
								+ this.userName);
					} else if (!line.startsWith("withWho")) {
					
						ServerWorker
								.sendAllClients(this.userName + ": " + line);
					} else if (inMsg[1].equals("privateTure")) {
System.out.println("    [----------]        "+line);
						String command = "";
						if(inMsg.length >= 5){//privateTalk&88&99&90
							command = "&"+inMsg[4];
						}else{
							
							//存储聊天记录
							
							DbUtil dbUtil = ServerWorker.getDbUtil();
							SimpleDateFormat sdf = new SimpleDateFormat("yyyy-M-d-h:m:s");
							String msgDate =  sdf.format(new Date());
							String sql = "insert into chatMsg(from_User_Number,to_User_Number,msg,msg_Date) "
									+ "values('"
									+ this.userName
									+ "','"
									+ inMsg[2]
									+ "','"
									+ inMsg[3]
									+ "','"
									+ msgDate + "')";
							
							dbUtil.execute(sql);
							//数据录入数据库
							
							
						}
//String str = inMsg[2]+ "privateTalk"+ "&" + this.userName + "&" + inMsg[2] + "&"+ inMsg[3]+command;
//System.out.println("    [----------]        "+str);
						if (ServerWorker.sendOneClient(inMsg[2], "privateTalk"
								+ "&" + this.userName + "&" + inMsg[2] + "&"
								+ inMsg[3]+command)) {

							out.println("privateTalk" + "&" + this.userName
									+ "&" + inMsg[2] + "&" + inMsg[3]);
							out.flush();
						} else {
							out.println(inMsg[2] + ResourceBundler.getString("Server.Quit.Private.Info"));
							out.flush();
						}
					} else {//withWho&a&d&抖屏
						String command = "";
						if(inMsg.length >= 5){
							command = "&"+inMsg[4];
						}
						ServerWorker.sendAllClients("withWho" + "&"
								+ this.userName + "&" + inMsg[2] + "&"
								+ inMsg[3]+command);
					}
				}
			} catch (IOException e) {
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
	private PrintWriter out;
	private String userName = null;
	private String sex = null;
	private String imageName = null;
	private int userID;

}
