import java.util.Scanner;

public class Example2_05
{
	Public static void main(String args[])
	{
		Scanner reader=new Scanner(System.in);
		
		double a,b,c;
		double area,perim,s;

		System.out.print("�������ߵĳ��ȣ�");
		
		a=reader.nextDouble();//�������߳���
		b=reader.nextDouble();
		c=reader.nextDouble();
		
		perim=a+b+c;
		s=perim/2;
		area=Math.sqrt(s*(s-a)*(s-b)*(s-c));
		
		System.out.println("�����ε����߳��ǣ�"+a+","+b+","+c);
		System.out.printf("�����ε������%.2f,",area);
		System.out.printf("�����ε��ܳ���%.2f\n",perim);
	}
}
