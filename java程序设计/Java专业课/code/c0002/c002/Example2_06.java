import java.util.Scanner;
public class Example2_06
{
	Public static void main(String args[])
	{
		int a,b,max;
		Scanner reader=new Scanner(System.in);
		
		System.out.print("����������������");
		a=reader.nextInt();
		b=reader.nextInt();
		
		max=a;//�ȼ����������a
		
		if(a<b)//���жϣ���������д�ɡ�max<b��
			max=b;
		
		System.out.println("�����ǣ�"+max);
	}
}
