import java.util.Scanner;

public class Example2_20
{
	public static void main(String args[])
	{
		int a,b,x,i;
		int counter=0;//��������������
		boolean prime=true;
		Scanner input=new Scanner(System.in);
		
		System.out.print("����������Ȼ����");
		a=input.nextInt();
		b=input.nextInt();
		
		if(a>b)//������������ֵ��ʹ��aС��b��
		{
			x=a;//������������ͨ����3����ʵ��
			a=b;
			b=x;
		}
		
		x=a%2==0?a+1:a;//x��������ʼ��ż������������
		
		while(x<=b)//��whileѭ��
		{
			prime=true;//�ȼ���x������
			
			//ͨ��ѭ���ٽ�һ��ȷ�ϣ�ѭ��Ƕ��
			for(i=2;i<=(int)Math.sqrt(x)&&prime;i++)
				if(x%i==0)
					prime=false;
			
			if(prime)
			{
				System.out.printf("%5d", x);
				
				counter++;
				if(counter%10==0) //ÿ�����10������
					System.out.println();
			}
			
			x+=2;//ֻ�ж�����
		}
		if(counter%10!=0)//���һ�в���10��ʱҲҪ����
			System.out.println();
		System.out.printf("�ܹ�%d��������", counter);
	}
}
