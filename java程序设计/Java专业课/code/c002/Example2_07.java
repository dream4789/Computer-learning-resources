import java.util.Scanner;

public class Example2_07
{
	public static void main(String args[])
	{
		Scanner reader=new Scanner(System.in);
		
		double a,b,c;
		double area,perim,s;
		
		System.out.print("输入三边的长度：");
		
		a=reader.nextDouble();//读入三边长度
		b=reader.nextDouble();
		c=reader.nextDouble();
		
		if(a+b>c && a+c>b && b+c>a)//任意两边之和大于第三边
		{
			perim=a+b+c;
			s=perim/2;
			area=Math.sqrt(s*(s-a)*(s-b)*(s-c));
			
			System.out.println("三角形的三边长是："+a+","+b+","+c);
			System.out.printf("三角形的面积：%.2f,",area);
			System.out.printf("三角形的周长：%.2f\n",perim);
			
			return;//执行此语句，程序结束，下面的语句不再执行
		}
		
		System.out.println("所给的三边不能构成三角形！");
	}
}
