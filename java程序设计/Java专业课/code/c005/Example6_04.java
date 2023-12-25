import java.util.Scanner;
class MyException extends Exception//自定义异常类，必须基于Exception派生
{
	String message;//定义String类型变量，用于提示信息  
	public MyException(String error)
	{ 
		message = error;  
	}  
	public String getMessage()
	{ // 重写getMessage()方法  
		return message;  
	}  
}

public class Example6_04
{
	public static void main(String[] args)
	{
		try
		{
			Scanner scanner=new Scanner(System.in);
			System.out.println("请输入用户的姓名、年龄：");
			String name=scanner.next();
			int age=scanner.nextInt();
			
			if(age<0)//如果年龄为负数，则抛出异常
				throw new MyException("年龄不能为负");//抛出MyException异常对象
			
			System.out.println("该用户的基本信息是：");
			System.out.println("姓名："+name+"， 年龄："+age);
		}
		catch (MyException e)
		{//捕获并处理MyException异常
			System.err.println(e.getMessage());
		}
	}
}
