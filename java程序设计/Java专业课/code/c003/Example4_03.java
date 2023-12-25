import java.util.Scanner;

public class Example4_03
{
	public static void main(String args[])
	{
		int n;
		Scanner reader=new Scanner(System.in);
		
		System.out.print("输入一个正整数：");
		n=reader.nextInt();
		
		System.out.println("1到"+n+"的和值："+sum(n));
	}
	private static int sum(int n)//递归方法
	{
		if(n>1)
			return sum(n-1)+n;//直接调用自身
		else
			return 1;
	}
}
