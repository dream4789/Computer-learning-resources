class SuperClass
{
	int var;
	
	public void setSuperVar(int var)
	{
		this.var=var;
	}
	public int getSuperVar()
	{
		return var;
	}
}
class SubClass extends SuperClass
{
	int var;//��̳��Ը������ͬ�������Ǹ������
	
	public void setSubVar(int v)
	{
		var=v;//���ʱ�������������򣬷��ʲ����̳��Ը������
	}
	public int getSubVar()
	{
		return var;//���ʱ�������������򣬷��ʲ����̳��Ը������
	}
}
public class Example5_03
{
	public static void main(String args[])
	{
		SubClass obj=new SubClass();
		
		obj.setSubVar(20);
		obj.setSuperVar(-20);
		
		System.out.println("�������������ֵ��"+obj.getSubVar());
		System.out.println("�������̳и�������ֵ��"+obj.getSuperVar());
	}
}
