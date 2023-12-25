package C009_Database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Date;
import java.util.Enumeration;
import java.util.Vector;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
* project_name:Java_Ex
*
* package_name:C009_Database
*
* author DarlingKe
* 
* version Created Time：2018年5月21日 下午12:23:14
*
* FileName:MyDBConnectionPool.java
*
* Description:数据库连接池文件
*/
public class MyDBConnectionPool {
	
	private static final Log logger = LogFactory.getLog(MyDBConnectionPool.class);
	
	public MyDBConnectionPool(String url,String user,String password,int normalConn,int maxConn){
		this.url = url;
		this.user = user;
		this.password= password;
		this.normalConnections = normalConn;
		this.maxConnections = maxConn;
		for(int i=0;i<normalConnections;i++){
			Connection conn = newConnection();
			if(conn!=null){
				freeConnections.addElement(conn);
				numOfFree++;
			}
		}
	}
	
	private Connection newConnection(){
		Connection conn = null;
		try{
			conn = DriverManager.getConnection(url,user,password);
			logger.info("通过连接池创建一个新连接.");
		}catch(SQLException sqle){
			logger.info("无法创建连接."+url);
			return null;
		}
		return conn;
	}
	
	public synchronized void freeConnection(Connection conn){
		freeConnections.addElement(conn);
		numOfFree++;
		checkedOut--;
		numOfActive--;
		notifyAll();
	}
	
	public int getnumOfFree(){
		return numOfFree;
	}
	
	public int getnumOfActive(){
		return numOfActive;
	}
	
	public int getnumOfMax(){
		return maxConnections;
	}
	
	//get a usable connection.
	@SuppressWarnings("resource")
	public synchronized Connection getConnection(){
		Connection conn = null;
		if(freeConnections.size()>0){
			numOfFree--;
			conn = (Connection) freeConnections.firstElement();
			freeConnections.removeElementAt(0);
			try{
				if(conn.isClosed()){
					logger.info("删除连接池中一个无效连接.");
					conn = getConnection();
				}
			}catch(SQLException sqle){
				logger.info("删除连接池中一个无效连接.");
				conn = getConnection();
			}
		}else if(maxConnections==0||checkedOut<maxConnections){
			conn = newConnection();
		}
		if(conn!=null)
			checkedOut++;
		numOfActive++;
		return conn;		
	}
	//get a usable connection within a given waiting time.
	public synchronized Connection getConnection(long timeout){
		long starttime = new Date().getTime();
		Connection conn;
		while((conn=getConnection())==null){
			try{
				wait(timeout);
			}catch(InterruptedException e){
				logger.info("等待获取连接异常.");
			}
			if((new Date().getTime()-starttime)>timeout)
				return null;
		}
		
		return conn;
	}
	
	//close all connections.
	public synchronized void release(){
		@SuppressWarnings("rawtypes")
		Enumeration allConnections = freeConnections.elements();
		while(allConnections.hasMoreElements()){
			Connection conn = (Connection) allConnections.nextElement();
			try{
				conn.close();
				numOfFree--;
			}catch(SQLException sqle){
				logger.info("关闭连接池中连接异常.");
			}
		}
		freeConnections.removeAllElements();
		numOfActive = 0;
	}
	
	private int checkedOut;
	private static Vector<Connection> freeConnections = new Vector<Connection>();
	private int maxConnections;
	private int normalConnections;
	private String url;
	private String user;
	private String password;
	private static int numOfFree = 0;
	private static int numOfActive = 0;
}
