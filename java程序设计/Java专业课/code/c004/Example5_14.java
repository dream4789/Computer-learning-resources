class Person
{
	public void doing()
	{
		System.out.println("����������......");
	}
}
public class Example5_14
{
	public static void main(String args[])
	{
		Person aPerson=new Person();
		aPerson.doing();
		
		aPerson=new Person()//�����������
		{//���������࣬����Person�������
			public void doing()//��д�����еķ���
			{
				System.out.println("ѧ��������ѧϰ��");
			}
		};//ע�⣬һ�����д�ڶ��У����˽���
		aPerson.doing();//ͨ�����������������еķ�������̬��
		
		aPerson=new Person()
		{//�����������ಢ��������
			public void doing()
			{
				System.out.println("��������������ɨ��");
			}
		};
		aPerson.doing();//��̬��
	}
}
