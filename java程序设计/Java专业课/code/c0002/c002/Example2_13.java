import java.util.Scanner;

public class Example2_13
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
		case 10:
		case 9:
			System.out.println("优秀");break;
		case 8:
			System.out.println("良好");break;
		case 7:
			System.out.println("中等");break;
		case 6:
			System.out.println("及格");break;
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		case 0:
			System.out.println("不及格");break;
		default://default放在最后
			System.out.println("成绩输入错误!");
		}
	}
}
