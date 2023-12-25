package ch12;
import java.sql.*;
import javax.sql.*;
public class Example12_5{
static Connection con = null;
static Statement st = null;
	public static void main(String[] para) {
		String url = "jdbc:mysql://localhost:3306/aaa";
		String user = "root";
		String password = "root";
		int insertNumber=0;
         String sql1 = "insert into selectCourse(studentNo,studentName,courseNo) values('0401060217','¶­·É ','0301E48W71'); ";
         String sql2 = "insert into selectCourse(studentNo,studentName,courseNo) values('0401060217','¶­·É ','0301E48W69'); ";
         String sql3 = "insert into selectCourse(studentNo,studentName,courseNo) values('0401060219','º«·É ','0301E48W71'); ";
		try{
		Class.forName("com.mysql.jdbc.Driver");
		con = DriverManager.getConnection(url,user,password);
		st = con.createStatement();
        insertNumber+=st.executeUpdate(sql1);
        insertNumber+=st.executeUpdate(sql2);
        insertNumber+=st.executeUpdate(sql3);
        System.out.println("successfully insert  "+insertNumber+"  records.");
        if(st!=null)
              st.close();
        if(con!=null) 
              con.close();
		}
		catch(ClassNotFoundException e1){System.out.println(e1.getMessage());}
		catch(SQLException e2){System.out.println(e2.getMessage());}
        	}
