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
          	//���ɵ�������ڻ�ÿɸ�����ָ��ɹ��������
  			st = con.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,
ResultSet.CONCUR_UPDATABLE);
          	rs = st.executeQuery(sql);
         		rs.last();      //ָ���ƶ�����������һ��
          	int count = rs.getRow();  //���������
    	   		for(int i=count;i>0;i--)
    	   		{
    		   		rs.absolute(i);      //ָ���ƶ����������i��
    		  		 System.out.println("��  "+i+" �м�¼�����£�");
    	  	   		temp = rs.getInt("studentAge");
    	  	   		rs.updateInt(3, temp+1);
    	  	  		 rs.updateRow();  //��ײ����ݿ��ύ�޸�
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
