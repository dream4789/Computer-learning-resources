import java.util.Scanner;

public class Example2_03
{
	public static void main(String args[])
	{
		double score,total=0;
		int counter=0;
		Scanner input=new Scanner(System.in);
		
		System.out.println("输入若干学生成绩，以任一字符（串）结束：");
		
		while(input.hasNextDouble())
		{
			score=input.nextDouble();
			
			total+=score;
			counter++;
		}
		
		System.out.printf("总成绩：%.1f,",total);
		System.out.printf("平均成绩：%.1f\n",total/counter);
	}
}
