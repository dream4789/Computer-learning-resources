import java.util.Scanner;

public class Example2_10
{
	public static void main(String args[])
	{
		int score;
		String grade;
		Scanner reader=new Scanner(System.in);
		
		System.out.print("输入成绩：");
		score=reader.nextInt();
		
		if(score>=90)
			grade="优秀";
		else if(score>=80)
			grade="良好";
		else if(score>=70)
			grade="中等";
		else if(score>=60)
			grade="及格";
		else
			grade="不及格";
		
		System.out.println("成绩等级为："+grade);
	}
}
