import java.util.Scanner;

public class Example2_03
{
	public static void main(String args[])
	{
		double score,total=0;
		int counter=0;
		Scanner input=new Scanner(System.in);
		
		System.out.println("��������ѧ���ɼ�������һ�ַ�������������");
		
		while(input.hasNextDouble())
		{
			score=input.nextDouble();
			
			total+=score;
			counter++;
		}
		
		System.out.printf("�ܳɼ���%.1f,",total);
		System.out.printf("ƽ���ɼ���%.1f\n",total/counter);
	}
}
