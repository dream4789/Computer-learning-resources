import java.util.InputMismatchException;
import java.util.Scanner;
public class Example6_03
{
	public static void main(String[] args) 
	{
		Scanner scanner=new Scanner(System.in);
		System.out.println("��������������ɳ������㣺");
		
		try
		{
			int a=scanner.nextInt();
			int b=scanner.nextInt();
			if(b==0) 
				throw new ArithmeticException();//�׳��쳣
			System.out.println("a/b��ֵ�ǣ�" + a/b);
		}
		catch (ArithmeticException e)
		{
			System.out.println("��������쳣������b����Ϊ0��");
		}
		catch(InputMismatchException e)
		{
			System.out.println("�����������ʹ����������������ݣ�");
		}
		
		System.out.println("���������");
	}
}
