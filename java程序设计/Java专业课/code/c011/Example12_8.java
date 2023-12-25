package ch12;
import javax.sql.*;
import javax.naming.*;
import java.util.*;
import java.sql.*;
public class Example12_8
{
public static void main(String[] args)
{
    	Connection con=null;   //定义连接类对象
        	PreparedStatement ps;  //定义编译预处理类对象ps
        	try
        	{
            	Class.forName("com.mysql.jdbc.Driver");  
            	     String url = "jdbc:mysql://localhost:3306/aaa";
                 con=DriverManager.getConnection(url,"root","root");
        	    	String sql = "update student set specialty =?  where  studentName= ?";
            	ps=con.prepareStatement(sql);
            	ps.setString(1,"软件工程");     //设置参数1
            	ps.setString(2, "李明");        //设置参数2
              int rowCount = ps.executeUpdate();  //执行更新操作 
              System.out.println(rowCount+"  record(s) updated.");
                ps.close();
con.close();
           }
           catch(Exception e) {}
       }
}
