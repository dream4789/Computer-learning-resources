package ch12;
import javax.sql.*;
import javax.naming.*;
import java.util.*;
import java.sql.*;
public class Example12_8
{
public static void main(String[] args)
{
    	Connection con=null;   //�������������
        	PreparedStatement ps;  //�������Ԥ���������ps
        	try
        	{
            	Class.forName("com.mysql.jdbc.Driver");  
            	     String url = "jdbc:mysql://localhost:3306/aaa";
                 con=DriverManager.getConnection(url,"root","root");
        	    	String sql = "update student set specialty =?  where  studentName= ?";
            	ps=con.prepareStatement(sql);
            	ps.setString(1,"�������");     //���ò���1
            	ps.setString(2, "����");        //���ò���2
              int rowCount = ps.executeUpdate();  //ִ�и��²��� 
              System.out.println(rowCount+"  record(s) updated.");
                ps.close();
con.close();
           }
           catch(Exception e) {}
       }
}
