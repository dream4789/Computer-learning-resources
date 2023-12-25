package ch12;
import java.io.*;
import java.sql.*;
import java.util.ArrayList;
import com.mchange.v2.c3p0.ComboPooledDataSource;
//Bean类
class Student
{
	String studentNo;
	String studentName;
	int studentAge;
	String specialty;
	public void setStudentNo(String sn)
{
		studentNo = sn;
	}
	public void setStudentName(String name)
{
		studentName = name;
	}
	public void setStudentAge(int age){
		studentAge = age;
	}
	public void setSpecialty(String specialty)
{
		this.specialty = specialty;
	}
	public String getStudentNo()
{
		return studentNo;
	}
	public String getStudentName()
{
		return studentName;
	}
	public int getStudentAge()
{
		return studentAge;
	}
	public String getSpecialty()
{
		return specialty;
	}
}
// DAO的父类
class BaseDao
 {
      ComboPooledDataSource ds;  //数据源对象
      // 在构造方法中返回数据源对象
public BaseDao () {
	 try
 {
	      ds=new ComboPooledDataSource();
           ds.setDriverClass("com.mysql.jdbc.Driver");
           ds.setJdbcUrl("jdbc:mysql://localhost:3306/aaa");
           ds.setUser("root");
           ds.setPassword("root");
           ds.setMaxPoolSize(40);
           ds.setMinPoolSize(2);
           ds.setInitialPoolSize(10);
           ds.setMaxStatements(180);
	  }catch(Exception ne)
{
	     System.out.println("Exception:"+ne);
	  }
	  }
       // 返回一个连接对象
	  public Connection getConnection()throws Exception
{
		 return ds.getConnection(); 
	  }
}
  //定义一个DAO子类,可以根据业务需要定义DAO的不同子类
class StudentDao extends BaseDao
{
       // 插入一条学生记录
       public boolean addStudent(Student student)
{  	  
   	      String sql = "INSERT INTO student" +
   	   		"(studentNo,studentName,studentAge,specialty) VALUES(?,?,?,?)";	   
   	      try( Connection conn = ds.getConnection();
   		 PreparedStatement pstmt = conn.prepareStatement(sql))
   	   { 
   	       pstmt.setString(1,student.getStudentNo());
   	       pstmt.setString(2,student.getStudentName());
   	       pstmt.setInt(3,student.getStudentAge());
   	       pstmt.setString(4,student.getSpecialty());
   	       pstmt.executeUpdate();
   	       return true;
   	      }catch(SQLException se)
{
   	  	     se.printStackTrace();
   		     return false;
   	      }
       } 
       // 按姓名检索客户记录
       public Student findByName(String name)
{ 
	      String sql = "SELECT * FROM student WHERE studentName=?";
           Student  student = new Student();
           try( Connection conn = ds.getConnection();
    	      PreparedStatement pstmt = conn.prepareStatement(sql))
{ 
   	         pstmt.setString(1,name);
   	         try(ResultSet rst = pstmt.executeQuery())
{
   	             if(rst.next())
{
   	                  student.setStudentNo(rst.getString("studentNo"));
   	                  student.setStudentName(rst.getString("studentName"));
   	                  student.setStudentAge(rst.getInt("studentAge"));
   	                  student.setSpecialty(rst.getString("specialty"));
   	             }
   	         }
          }catch(SQLException se)
{
   	  	     return null;
   	      }
   	      return student;
       }
       // 查询所有学生信息
       public ArrayList<Student> findAllStudent()
{  	  
   	      Student  student = new Student();
   	      ArrayList<Student> studentList = new ArrayList<Student>();
   	      String sql = "SELECT * FROM student";
   	      try( Connection conn = ds.getConnection();
   		 PreparedStatement pstmt = conn.prepareStatement(sql);
   		 ResultSet rst = pstmt.executeQuery())
{  		 
   	          while(rst.next())
{
   	              student.setStudentNo(rst.getString("studentNo"));
   	              student.setStudentName(rst.getString("studentName"));
   	              student.setStudentAge(rst.getInt("studentAge"));
   	              student.setSpecialty(rst.getString("specialty"));	
   	              studentList.add(student);	
   	         }	     
   	         return studentList;
   	        }catch(SQLException e){
   	      e.printStackTrace();
   		 return null;
   	  }
   }
}
//测试程序，仅进行了数据添加
public class Example12_9
{
    public static void main(String []para)
{
StudentDao dao = new StudentDao();
//student's attributes may come from web page submitted in jsp
Student student = new Student();
student.setStudentNo("1401010191");
student.setStudentName("hanfei");
student.setStudentAge(15);
student.setSpecialty("network");
if(dao.addStudent(student))  
System.out.println("successfully insert a student into table student.");
         else 
System.out.println("what is wrong with the insert operation?");
          }
}
