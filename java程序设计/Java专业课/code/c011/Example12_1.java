package ch12;
import java.sql.*;
import javax.sql.*;

public class Example12_1 {
	public static void main(String[] para) {
		Connection con = null;
		String url = "jdbc:mysql://localhost:3306/aaa";
		String user = "root";
		String password = "root";
		try{
		Class.forName("com.mysql.jdbc.Driver");
		con = DriverManager.getConnection(url,user,password);
		if(con!=null) System.out.println("���ݿ����ӳɹ���");
		else System.out.println("���ݿ�����ʧ�ܣ�");
		}
		catch(ClassNotFoundException e1){}
		catch(SQLException e2){}
	}
}
