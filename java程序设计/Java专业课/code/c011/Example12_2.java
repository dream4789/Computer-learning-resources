package ch12;
import java.sql.*;
import javax.sql.*;

class Example12_2
{         
  		static Connection con=null;   //���Ӷ���
  		static Statement st = null;
static ResultSet rs = null;
public static boolean conn(String url)
{
    		try
{
  	  			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");//������������
				con=DriverManager.getConnection(url);  //�������ݿ�
}
catch(Exception e)
{
e.printStackTrace(); 
return false;
}
return true;      //�ɹ�
}
  		public static boolean close()
{
    		try
{		
      			con.close();   //�ر����ݿ�
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
//Driver ����ӿո񣬷��������쳣��
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
