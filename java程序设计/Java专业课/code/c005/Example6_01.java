import java.util.InputMismatchException;
import java.util.Scanner;
public class Example6_01
{
	public static void main(String[] args)
	{
		Scanner scanner=new Scanner(System.in);
		System.out.println("��������������ɳ������㣺");
		
		try
		{ // �쳣�Ĳ�������
			int a=scanner.nextInt();
			int b=scanner.nextInt();
			System.out.println("a/b��ֵ�ǣ�" + a/b);
		}
		catch (ArithmeticException e)
		{ // catch��׽ArithmeticException�쳣
			System.out.println("��������쳣������b����Ϊ0��");
		}
		catch(InputMismatchException e)
		{ // catch��׽InputMismatchException�쳣
			System.out.println("�����������ʹ����������������ݣ�");
		}
		
		System.out.println("���������");
	}
}
