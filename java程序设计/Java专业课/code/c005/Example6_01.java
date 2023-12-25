import java.util.InputMismatchException;
import java.util.Scanner;
public class Example6_01
{
	public static void main(String[] args)
	{
		Scanner scanner=new Scanner(System.in);
		System.out.println("输入两个整数完成除法运算：");
		
		try
		{ // 异常的捕获区域
			int a=scanner.nextInt();
			int b=scanner.nextInt();
			System.out.println("a/b的值是：" + a/b);
		}
		catch (ArithmeticException e)
		{ // catch捕捉ArithmeticException异常
			System.out.println("程序出现异常，除数b不能为0。");
		}
		catch(InputMismatchException e)
		{ // catch捕捉InputMismatchException异常
			System.out.println("输入数据类型错误，请输入整型数据！");
		}
		
		System.out.println("程序结束。");
	}
}
