public class Example4_11
{
	public static void main(String args[])
	{
		int a[]={23,93,84,78,48,28,92,38,46};
		
		System.out.println("��main()����������ĵ�ַ��"+a);
		System.out.println("������ԭʼֵ��");
		print(a);//ʵ��������
		System.out.println("----------����add()����------------");
		
		add(a);//ʵ��������
		System.out.println("���÷���add()��������Ԫ��ֵ��");		
		print(a);//ʵ��������
		
		System.out.println("----------����sort()����-----------");
		sort(a);//ʵ��������
		System.out.println("���÷���sort()�����������Ԫ��ֵ��");		
		print(a);//ʵ��������
	}
	private static void print(int x[])//��������и�Ԫ�أ��β�������
	{
		for(int a:x)
			System.out.printf("%3d",a);
		System.out.println();
		//System.out.println("��print()����������ĵ�ַ��"+x);
	}
	private static void add(int x[])//�ı�����Ԫ�ص�ֵ���β�������
	{
		System.out.println("��add()����������ĵ�ַ��"+x);
		for(int i=0;i<x.length;i++)
			x[i]=x[i]+5;//ÿ��Ԫ�ض���5
	}
	private static void sort(int x[])//�����β�������
	{
		System.out.println("��sort()����������ĵ�ַ��"+x);
		int i,j,k;
		
		for(i=0;i<x.length-1;i++)
		{
			k=i;
			for(j=i+1;j<x.length;j++)
				if(x[k]>x[j])
					k=j;
			
			if(k!=i)
			{
				int t=x[i];
				x[i]=x[k];
				x[k]=t;
			}
		}
	}
}
