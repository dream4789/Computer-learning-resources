interface Charge//�ӿ�����
{
	public void �շ�();//���󷽷�
}
class Cinema implements Charge//��ӰԺ�࣬ʵ�ֽӿ�
{
	public void �շ�()
	{
		System.out.println("��ӰƱ10Ԫһ�š�");
	}
}
class Taxi implements Charge//���⳵�࣬ʵ�ֽӿ�
{
	public void �շ�()
	{
		System.out.println("���⳵����9.9Ԫ");
	}
}
class Highway implements Charge//���ٹ�·�࣬ʵ�ֽӿ�
{
	public void �շ�()
	{
		System.out.println("���ٹ�·�շ�25.0Ԫ");
	}
}
class Mountainimplements Charge//ɽ�࣬ʵ�ֽӿ�
{
	public void �շ�()
	{
		System.out.println("��ɽ��Ʊ120Ԫ");
	}
}
public classExample5_18
{
	public static void main(String args[])
	{
		Charge charge;//�����ӿڱ���
		
		charge=new Cinema();//�ӿڱ�����ʾ��ӰԺ����
		charge.�շ�();//��̬��
		
		charge=new Taxi();//�ӿڱ�����ʾ���⳵����
		charge.�շ�();//��̬��
		
		charge=new Highway();//�ӿڱ�����ʾ���ٹ�·����
		charge.�շ�();//��̬��
		
		charge=new Mountain();//�ӿڱ�����ʾ��ɽ����
		charge.�շ�();//��̬��		
	}
}
