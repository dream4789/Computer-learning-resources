import java.util.Scanner;

public class Example2_24
{
	public static void main(String args[])
	{
		int sum=0,x;
		Scanner reader=new Scanner(System.in);
		
		System.out.println("输入若干个正整数，以负数结束：");
		
		while((x=reader.nextInt())>0)
		{
			if(x%3==0)
				continue;//与continue在同一循环体内还有下面一条语句
				//当执行到continue语句后，当前循环的下面语句不被执行，
				//继续下一次循环
			sum=sum+x; 
		}
		
		System.out.println("sum="+sum);
	}
}
