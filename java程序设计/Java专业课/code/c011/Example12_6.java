package ch12;
import java.sql.*;
import javax.sql.*;
public class Example12_6{
static Connection con = null;
static Statement st = null;
static ResultSet rs = null;
	public static void main(String[] para) {
		String url = "jdbc:mysql://localhost:3306/aaa";
		String user = "root";
		String password = "root";
  	    String sql ="select * from student";
  	    int temp=0;
  	    try{
  			Class.forName("com.mysql.jdbc.Driver");
  			con = DriverManager.getConnection(url,user,password);
          	//生成的语句用于获得可更新且指针可滚动结果集
  			st = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
ResultSet.CONCUR_UPDATABLE);
          	rs = st.executeQuery(sql);
         		rs.last();      //指针移动到结果集最后一行
          	int count = rs.getRow();  //结果集行数
    	   		for(int i=count;i>0;i--)
    	   		{
    		   		rs.absolute(i);      //指针移动到结果集第i行
    		  		 System.out.println("第  "+i+" 行记录被更新！");
    	  	   		temp = rs.getInt("studentAge");
    	  	   		rs.updateInt(3, temp+1);
    	  	  		 rs.updateRow();  //向底层数据库提交修改
    	    		}
          	if(st!=null)
              	st.close();
         		 if(con!=null) 
              	con.close();
  			}
  			catch(ClassNotFoundException e1){System.out.println(e1.getMessage());}
  			catch(SQLException e2){System.out.println(e2.getMessage());}
   		}
}
