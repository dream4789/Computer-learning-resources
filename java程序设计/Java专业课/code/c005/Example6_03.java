import java.util.InputMismatchException;
import java.util.Scanner;
public class Example6_03
{
	public static void main(String[] args) 
	{
		Scanner scanner=new Scanner(System.in);
		System.out.println("输入两个整数完成除法运算：");
		
		try
		{
			int a=scanner.nextInt();
			int b=scanner.nextInt();
			if(b==0) 
				throw new ArithmeticException();//抛出异常
			System.out.println("a/b的值是：" + a/b);
		}
		catch (ArithmeticException e)
		{
			System.out.println("程序出现异常，除数b不能为0。");
		}
		catch(InputMismatchException e)
		{
			System.out.println("输入数据类型错误，请输入整型数据！");
		}
		
		System.out.println("程序结束。");
	}
}
