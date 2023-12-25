package ch12；
 import java.io.*;
 import java.util.Iterator;
 import java.sql.*;
 import java.util.Properties;
 import javax.sql.rowset.*;
 import javax.sql.rowset.RowSetProvider;
 import javax.sql.rowset.RowSetFactory;

 public class Example12_7
{
   private String driver;
   private String url;
   private String user;
   private String password;
   public void initParam(String paramFile) throws Exception
{
Properties props = new Properties();
props.load(new FileInputStream(paramFile));
driver = props.getProperty("driver");
url = props.getProperty("url");
user = props.getProperty("user");
password =  props.getProperty("password");
}
  public void update(String sql) throws Exception
{
 	  int temp; 
       Class.forName(driver);
 RowSetFactory factory = RowSetProvider.newFactory();
 try( JdbcRowSet jdbcrs = factory.createJdbcRowSet())
{
jdbcrs.setUrl(url);
jdbcrs.setUsername(user);
jdbcrs.setPassword(password);
jdbcrs.setCommand(sql);
jdbcrs.execute();
jdbcrs.afterLast();
while(jdbcrs.previous())
{
System.out.println(jdbcrs.getString(1)+ "\t"+jdbcrs.getString(2)
    						 + "\t"+jdbcrs.getString(3));
temp = jdbcrs.getInt("studentAge");
jdbcrs.updateInt("studentAge",temp+1);
jdbcrs.updateRow();
} 
}
}

public static void main(String[] args) throws Exception
{
JdbcRowSetTest jrst = new JdbcRowSetTest();
jrst.initParam("mysql.property");//属性文件要配置在项目的根目录下
jrst.update("select * from student");
}
}
