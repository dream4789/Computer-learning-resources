class ѧ��//����
{
	String ѧ��;//ѧ�����е�����
	String ����;
	char �Ա�;
	int ����;
	
	//���еĲ���
	void ����ѧ����Ϣ(String no,String name,char gender,int age)
	{
		ѧ��=no;
		����=name;
		�Ա�=gender;
		����=age;
	}
	public String ѧ����Ϣ()
	{
		String str=ѧ��+" "+����+" ";
		str+=(�Ա�=='m'?"��":"Ů")+����+"��";
		return str;
	}	
}
class ��ѧ�� extends ѧ��//���ඨ��
{
	int ��ѧ,����;//��ѧ���γ�
	
	void ��д��ѧ���ɼ�(int math,int chinese)
	{
		��ѧ=math;
		����=chinese;
	}
	
	public String ��ѧ���ɼ�()
	{
		String str="��ѧ��"+��ѧ+",����"+����;
		return str;
	}
	void print()
	{
		System.out.print(ѧ����Ϣ()+" ");
		System.out.println(��ѧ���ɼ�());
	}
}
class ��ѧ�� extends ѧ��//���ඨ��
{
	int ����,Java;//��ѧ���γ�
	
	void ��д��ѧ���ɼ�(int math,int prog)
	{
		����=math;
		Java=prog;
	}
	
	public String ��ѧ���ɼ�()
	{
		String str="�ߵ���ѧ��"+����+",Java��"+Java;
		return str;
	}
	
	void print()
	{
		System.out.print(ѧ����Ϣ()+" ");
		System.out.println(��ѧ���ɼ�());
	}
}
public class Example5_02
{
	public static void main(String args[])
	{
		��ѧ������=new ��ѧ��();
		����.����ѧ����Ϣ("160101", "����", 'f', 15);
		����.��д��ѧ���ɼ�(90, 91);
		
		��ѧ������=new ��ѧ��();
		����.����ѧ����Ϣ("0416010101", "����", 'm', 19);
		����.��д��ѧ���ɼ�(80, 81);
		
		����.print();
		����.print();
	}
}
