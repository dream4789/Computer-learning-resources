import java.util.Scanner;

public class Example2_19
{
	public static void main(String args[])
	{
		int x,i;
		boolean prime=true;//�ȼ���x������
		Scanner input=new Scanner(System.in);
		
		System.out.print("����һ����Ȼ����");
		x=input.nextInt();

		//ͨ��ѭ���ж��Ƿ�������
		for(i=2;i<=x-1;i++)//i��2~(x-1)֮��
			if(x%i==0)//i��x������
				prime=false;
		
		System.out.print(x);
		if(prime)
			System.out.println("��������");
		else
			System.out.println("����������");
	}
}
