import java.util.Scanner;

public class Example2_20
{
	public static void main(String args[])
	{
		int a,b,x,i;
		int counter=0;//素数个数计数器
		boolean prime=true;
		Scanner input=new Scanner(System.in);
		
		System.out.print("输入两个自然数：");
		a=input.nextInt();
		b=input.nextInt();
		
		if(a>b)//交换两个数的值，使得a小、b大
		{
			x=a;//交换两个数得通过第3个数实现
			a=b;
			b=x;
		}
		
		x=a%2==0?a+1:a;//x从奇数开始，偶数不能是素数
		
		while(x<=b)//用while循环
		{
			prime=true;//先假设x是素数
			
			//通过循环再进一步确认，循环嵌套
			for(i=2;i<=(int)Math.sqrt(x)&&prime;i++)
				if(x%i==0)
					prime=false;
			
			if(prime)
			{
				System.out.printf("%5d", x);
				
				counter++;
				if(counter%10==0) //每行输出10个素数
					System.out.println();
			}
			
			x+=2;//只判断素数
		}
		if(counter%10!=0)//最后一行不足10个时也要换行
			System.out.println();
		System.out.printf("总共%d个素数。", counter);
	}
}
