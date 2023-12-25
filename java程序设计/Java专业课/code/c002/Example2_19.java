import java.util.Scanner;

public class Example2_19
{
	public static void main(String args[])
	{
		int x,i;
		boolean prime=true;//先假设x是素数
		Scanner input=new Scanner(System.in);
		
		System.out.print("输入一个自然数：");
		x=input.nextInt();

		//通过循环判断是否有因子
		for(i=2;i<=x-1;i++)//i在2~(x-1)之间
			if(x%i==0)//i是x的因子
				prime=false;
		
		System.out.print(x);
		if(prime)
			System.out.println("是素数。");
		else
			System.out.println("不是素数。");
	}
}
