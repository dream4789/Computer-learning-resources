import java.util.Scanner;

public class Example2_12
{
	public static void main(String args[])
	{
		int score,grade;
		Scanner reader=new Scanner(System.in);
		
		System.out.print("输入成绩：");
		score=reader.nextInt();
		
		grade=score/10;
		
		switch(grade)
		{
		default: //default在最前面
			System.out.println("成绩输入错误!");
		case 10:
			System.out.println("优秀");
		case 9:
			System.out.println("优秀");
		case 8:
			System.out.println("良好");
		case 7:
			System.out.println("中等");
		case 6:
			System.out.println("及格");
		case 5:
			System.out.println("不及格");
		case 4:
			System.out.println("不及格");
		case 3:
			System.out.println("不及格");
		case 2:
			System.out.println("不及格");
		case 1:
			System.out.println("不及格");
		case 0:
			System.out.println("不及格");
		}
	}
}
