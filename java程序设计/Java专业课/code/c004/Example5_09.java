class A
{
	//���ų�����������
	public static final double PI=3.1415926;
	
	int a=10;
	
	public final int getA()//���շ���
	{
		return a;
	}
}
class B extends A
{
	int b=-15;
	
	public B()
	{
		PI=2.71828;//Ϊ�̳��Ը�������������¸�ֵ
	}
	
	public int getA()//��д���෽��
	{
		return b;
	}
}
public class Example5_09
{
	public static void main(String args[])
	{
		B obj=new B();
		
		obj.PI=2.71828;//������Ϊ�������¸�ֵ
		
		System.out.println(obj.getA());
	}
}
