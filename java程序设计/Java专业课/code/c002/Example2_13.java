import java.util.Scanner;

public class Example2_13
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
		case 10:
		case 9:
			System.out.println("����");break;
		case 8:
			System.out.println("����");break;
		case 7:
			System.out.println("�е�");break;
		case 6:
			System.out.println("����");break;
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		case 0:
			System.out.println("������");break;
		default://default�������
			System.out.println("�ɼ��������!");
		}
	}
}
