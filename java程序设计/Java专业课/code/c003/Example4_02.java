public class Example4_02
{
	public static void main(String args[])
	{
		int a=10,b=25,c=-90;
		int x[]={98,34,78,934,8,93,48,928,92,8,83};
		
		System.out.println("�������е��������"+max(a,b));//���õ�1��max
		System.out.println("�������е��������"+max(a,b,c));//���õ�2��max
		System.out.println("������е��������"+max(x));//���õ�3��max
	}
	private static int max(int x,int y)//�������ط������βλ�����ͬ
	{
		return x>y?x:y;
	}
	private static int max(int x,int y,int z)
	{
		int m=max(x,y);//���õ�1��max������ǰ�����������
		return m>z?m:z;
	}
	private static int max(int a[])
	{
		int m=a[0];
		for(int x:a)
			m=m>x?m:x; 
		return m;
	}
}
