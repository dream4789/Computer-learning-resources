import java.util.Scanner;

public class Example2_10
{
	public static void main(String args[])
	{
		int score;
		String grade;
		Scanner reader=new Scanner(System.in);
		
		System.out.print("����ɼ���");
		score=reader.nextInt();
		
		if(score>=90)
			grade="����";
		else if(score>=80)
			grade="����";
		else if(score>=70)
			grade="�е�";
		else if(score>=60)
			grade="����";
		else
			grade="������";
		
		System.out.println("�ɼ��ȼ�Ϊ��"+grade);
	}
}
