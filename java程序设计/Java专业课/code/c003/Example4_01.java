public class Example4_01
{
	public static void main(String args[])
	{
		int x,y,z;
		
		x=10;
		y=25;
		z=add(x,y);//����ʱҲ����ֱ�Ӹ���������add(10,25)
		System.out.println(x+"+"+y+"="+z);
		//Ҳ����ֱ�������System.out.println(add(10,25));
		
		int m=max(x,y,z);
		System.out.printf("%d��%d��%d���������%d\n",x,y,z,m);
		
	}
	private static int add(int a,int b)//add��������������ֵ
	{
		int c=a+b;
		return c;
	}
	//���add�������¶��岻����
	/*private static int add(double a,double b)
	{�β�a��b����double����ӽ��Ҳ��double
	������������int����doubleת��Ϊintʱ����ִ���
		return a+b;
	}*/
	private static int max(int a,int b,int c)//max��������������ֵ
	{
	int max;
		max=a>b?a:b;
		max=max>c?max:c;
		return max;
	}
}
