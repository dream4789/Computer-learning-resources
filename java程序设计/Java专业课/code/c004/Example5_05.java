import static java.lang.System.out;
class Super
{
	int var;
	
	public Super(int var)
	{
		this.var=var;
	}
}
class Sub extends Super
{
	int var;
	
	public Sub(int var1,int var2)
	{
		super(var2);//���ø���Ĺ��췽��
		this.var=var1;//����thisҲ��
	}
	public void display()
	{
		out.println("�̳��Ը������"+super.var);//���ʱ����صĸ������
		out.println("���������"+var);//�����ඨ�����
	}
}
public class Example5_05
{
	public static void main(String ars[])
	{
		Sub sub=new Sub(10,-200);
		sub.display();
	}
}
