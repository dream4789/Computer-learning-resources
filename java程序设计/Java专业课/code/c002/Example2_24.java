import java.util.Scanner;

public class Example2_24
{
	public static void main(String args[])
	{
		int sum=0,x;
		Scanner reader=new Scanner(System.in);
		
		System.out.println("�������ɸ����������Ը���������");
		
		while((x=reader.nextInt())>0)
		{
			if(x%3==0)
				continue;//��continue��ͬһѭ�����ڻ�������һ�����
				//��ִ�е�continue���󣬵�ǰѭ����������䲻��ִ�У�
				//������һ��ѭ��
			sum=sum+x; 
		}
		
		System.out.println("sum="+sum);
	}
}
