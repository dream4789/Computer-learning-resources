import java.util.Random;

public class Example2_27
{
	public static void main(String args[])
	{
		int a[]=new int[10];
		
		getElements(a);//��4�����ֱ����ڵ�����Ӧ�ķ���
		print(a);
		sort(a);
		print(a);
	}
	private static void sort(int a[])//��������������
	{
		int i,j,t;
		
		for(i=0;i<a.length-1;i++)//����a.length-1��
		{
			for(j=0;j<a.length-1-i;j++)//ÿ�˱Ƚ�a.length-1-i��
				if(a[j]>a[j+1])//���ǰ�Ⱥ���򽻻�ֵ
				{
					t=a[j];
					a[j]=a[j+1];
					a[j+1]=t;
				}
		}
	}
	private static void getElements(int a[])//������Ϊ����Ԫ�ظ����ֵ
	{
		Random rand=new Random();//�������Ķ���
		
		for(int i=0;i<a.length;i++)
			a[i]=rand.nextInt(100);//ÿ�δ���һ��������100�������
	}
	private static void print(int a[])//������������������и�Ԫ��
	{
		for(int i=0;i<a.length;i++)
			System.out.printf("%3d", a[i]);
		System.out.println();
	}
}
