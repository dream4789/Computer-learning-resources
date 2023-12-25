import java.util.Scanner;

public class Example2_05
{
	Public static void main(String args[])
	{
		Scanner reader=new Scanner(System.in);
		
		double a,b,c;
		double area,perim,s;

		System.out.print("输入三边的长度：");
		
		a=reader.nextDouble();//读入三边长度
		b=reader.nextDouble();
		c=reader.nextDouble();
		
		perim=a+b+c;
		s=perim/2;
		area=Math.sqrt(s*(s-a)*(s-b)*(s-c));
		
		System.out.println("三角形的三边长是："+a+","+b+","+c);
		System.out.printf("三角形的面积：%.2f,",area);
		System.out.printf("三角形的周长：%.2f\n",perim);
	}
}
