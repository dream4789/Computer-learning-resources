package ch12;
import java.sql.*;
import javax.sql.*;

class Example12_2
{         
  		static Connection con=null;   //连接对象
  		static Statement st = null;
static ResultSet rs = null;
public static boolean conn(String url)
{
    		try
{
  	  			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");//加载驱动程序
				con=DriverManager.getConnection(url);  //连接数据库
}
catch(Exception e)
{
e.printStackTrace(); 
return false;
}
return true;      //成功
}
  		public static boolean close()
{
    		try
{		
      			con.close();   //关闭数据库
      			con=null;
}
catch(SQLException e)
{
e.printStackTrace();
return false;
}
    		return true;	
  		}
  		public static void main(String[] args)  throws Exception
{
String str=new String();
//Driver 后面加空格，否则会出现异常。
if(conn("jdbc:odbc:driver={Microsoft Access Driver (*.mdb)};
 					DBQ=d:\\xsgl.mdb"))
{
  		st = con.createStatement();
rs = st.executeQuery("select * from studentInfo");
while(rs.next())
{
System.out.print(rs.getString(1)+"     ");
System.out.println(rs.getString(2));
}
}                          
}
}
