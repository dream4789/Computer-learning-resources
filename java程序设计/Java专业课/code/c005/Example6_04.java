import java.util.Scanner;
class MyException extends Exception//�Զ����쳣�࣬�������Exception����
{
	String message;//����String���ͱ�����������ʾ��Ϣ  
	public MyException(String error)
	{ 
		message = error;  
	}  
	public String getMessage()
	{ // ��дgetMessage()����  
		return message;  
	}  
}

public class Example6_04
{
	public static void main(String[] args)
	{
		try
		{
			Scanner scanner=new Scanner(System.in);
			System.out.println("�������û������������䣺");
			String name=scanner.next();
			int age=scanner.nextInt();
			
			if(age<0)//�������Ϊ���������׳��쳣
				throw new MyException("���䲻��Ϊ��");//�׳�MyException�쳣����
			
			System.out.println("���û��Ļ�����Ϣ�ǣ�");
			System.out.println("������"+name+"�� ���䣺"+age);
		}
		catch (MyException e)
		{//���񲢴���MyException�쳣
			System.err.println(e.getMessage());
		}
	}
}
