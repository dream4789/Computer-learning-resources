class Base//����һ������
{
	int base_var1;//������
	double base_var2;
	
	void setBaseVar(int var1,double var2)//������������ֵ
	{
		base_var1=var1;
		base_var2=var2;
	}
	
	void basePrint()//��������ӡ��ֵ
	{
		System.out.print("base_var1="+base_var1+",");
		System.out.println("base_var2="+base_var2);
	}
}
class Derived extends Base//����һ������Base���������
{
	int derived_var1;//�����¶����������
	double derived_var2;
	
	void setDerivedVar(int var1,double var2)//������������ֵ
	{
		derived_var1=var1;
		derived_var2=var2;
	}
	
	void derivedPrint()//��������ӡ��ֵ
	{
		System.out.print("derived_var1="+derived_var1+",");
		System.out.println("derived_var2="+derived_var2);
	}
	
	void print()
	{
		System.out.print("base_var1="+base_var1+",");//���෽��ֱ�ӷ��ʼ̳��Ը������
		System.out.println("base_var2="+base_var2);
		System.out.print("derived_var1="+derived_var1+",");
		System.out.println("derived_var2="+derived_var2);
	}
}

public class Example5_01
{
	public static void main(String args[])
	{
		Derived derived=new Derived();//�������������
		
		derived.setBaseVar(10, 20);//ͨ�����������������ֵ
		derived.setDerivedVar(-15, -25);
		
		derived.basePrint();//ͨ������������ӡ��ֵ
		derived.derivedPrint();
		
		System.out.println("--------  �ٴ�ӡһ��  --------");
		derived.print();
	}
}
