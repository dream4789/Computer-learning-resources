package C009_Database;

import java.sql.Connection;
import java.sql.Driver;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
* project_name:Java_Ex
*
* package_name:C009_Database
*
* author DarlingKe
* 
* version Created Time：2018年5月21日 下午1:05:18
*
* FileName:MyPool.java
*
* Description:数据库连接池实现类
*/
public class MyPool {
	
	private MyPool(){
		loadDriver(driverClass);
		createPool();
	}
	
	public static synchronized MyPool getInstance(){
		if(instance==null)
			instance = new MyPool();
		return instance;
	}
	
	private void loadDriver(String driverClass){
		String driverClassName = driverClass;
		try{
			driver = (Driver) Class.forName(driverClassName).newInstance();
			DriverManager.registerDriver(driver);
		}catch(Exception e){
			System.out.println("Can not register JDBC driver:"+driverClassName);
		}
	}
	
	private void createPool(){
		pool = new MyDBConnectionPool(url,user,password,normalConnect,maxConnect);
		if(pool!=null)
			System.out.println("创建连接池成功.");
		else
			System.out.println("创建连接池失败.");
	}
	
	public Connection getConnection(){
		if(pool!=null)
			return pool.getConnection();
		return null;
	}
	
	public Connection getConnection(long time){
		if(pool!=null)
			return pool.getConnection(time);
		return null;
	}
	
	public void freeConnection(Connection conn){
		if(pool!=null)
			pool.freeConnection(conn);
	}
	
	public int getNumOfFree(){
		return pool.getnumOfFree();
	}
	
	public int getNumOfActive(){
		return pool.getnumOfActive();
	}
	
	public int getnumOfMax(){
		return pool.getnumOfMax();
	}
	
	public synchronized void release(){
		pool.release();
		try{
			DriverManager.deregisterDriver(driver);
			System.out.println("release JDBC Drivers: "+driver.getClass().getName());
		}catch(SQLException sqlex){
			System.out.println("Can not release JDBC Drivers: " + driver.getClass().getName());
		}
	}
	
	private static MyPool instance = null;
	private int maxConnect = 100;
	private int normalConnect = 10;
	private String url = "jdbc:mysql://localhost:3306/huaqi";
	private String user = "root";
	private String password = "root";
	private String driverClass = "com.mysql.jdbc.Driver";
	Driver driver = null;
	MyDBConnectionPool pool = null;
}
