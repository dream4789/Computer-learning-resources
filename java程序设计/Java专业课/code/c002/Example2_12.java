import java.util.Scanner;

public class Example2_12
{
	public static void main(String args[])
	{
		int score,grade;
		Scanner reader=new Scanner(System.in);
		
		System.out.print("����ɼ���");
		score=reader.nextInt();
		
		grade=score/10;
		
		switch(grade)
		{
		default: //default����ǰ��
			System.out.println("�ɼ��������!");
		case 10:
			System.out.println("����");
		case 9:
			System.out.println("����");
		case 8:
			System.out.println("����");
		case 7:
			System.out.println("�е�");
		case 6:
			System.out.println("����");
		case 5:
			System.out.println("������");
		case 4:
			System.out.println("������");
		case 3:
			System.out.println("������");
		case 2:
			System.out.println("������");
		case 1:
			System.out.println("������");
		case 0:
			System.out.println("������");
		}
	}
}
