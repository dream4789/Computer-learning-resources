import java.util.Scanner;
public class Example2_06
{
	Public static void main(String args[])
	{
		int a,b,max;
		Scanner reader=new Scanner(System.in);
		
		System.out.print("输入两个整型数：");
		a=reader.nextInt();
		b=reader.nextInt();
		
		max=a;//先假设最大数是a
		
		if(a<b)//再判断，条件还可写成“max<b”
			max=b;
		
		System.out.println("大数是："+max);
	}
}
