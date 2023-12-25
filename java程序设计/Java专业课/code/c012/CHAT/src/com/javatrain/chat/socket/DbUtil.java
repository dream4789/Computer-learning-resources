package com.javatrain.chat.socket;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.javatrain.chat.util.ResourceBundler;

//工具类
public class DbUtil {

	private static DbUtil dbUtil;
	private Connection con;

	private DbUtil() {
		try {
			Class.forName(ResourceBundler.getResourceBundle().getString(
					"jdbc.drivers"));
			getConnection();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void getConnection() throws SQLException {
		String url = ResourceBundler.getResourceBundle().getString("jdbc.url");
		String userName = ResourceBundler.getResourceBundle().getString(
				"jdbc.username");
		String pwd = ResourceBundler.getResourceBundle().getString(
				"jdbc.password");
		con = DriverManager.getConnection(url, userName, pwd);
	}

	public static DbUtil getInstance() {
		if (dbUtil == null) {
			dbUtil = new DbUtil();
		}
		return dbUtil;
	}

	public boolean execute(String sql) {
		Statement state = null;
		boolean isExecuteSuccess = false;
		try {
			state = con.createStatement();
			state.execute(sql);
			isExecuteSuccess = true;
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			try {
				state.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return isExecuteSuccess;
	}

	public ResultSet executeQuery(String sql) {
		ResultSet rs = null;
		Statement state = null;
		try {
			state = con.createStatement();
			rs = state.executeQuery(sql);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			/*try {
				state.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}*/
		}
		return rs;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String sql = "insert into chatMsg(from_User_Number,to_User_Number,msg,msg_Date) "
				+ "values('111','222','nihao','2011-8-23')";
		System.out.println(DbUtil.getInstance().execute(sql));
	}

}
