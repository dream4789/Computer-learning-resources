abstract class Transport//����Ľ�ͨ������
{
	int speed;
	String name;
	public Transport(){}//���췽��
	public Transport(String name,int speed)//���췽��
	{
		this.speed=speed;
		this.name=name;
	}
	public abstract void run();//���󷽷�
}
//�������ඨ��ͬ��5.13
public class Example5_16
{
	public static void main(String args[])
	{
		Transport aTransport;//����һ����ͨ������Ķ���
		
		//aTransport=new Transport();��������ΪTransport��һ��������
		
		aTransport=new Rocket("����4��",2200);//��ֵ���ݹ��򣬱�ʾ�������
		aTransport.run();//����run����
		
		aTransport=new Car("����",120);//��ʾ�γ�����
		aTransport.run();
		
		aTransport=new Plane("�տ�A320",800);//��ʾ�ɻ�����
		aTransport.run();
		
		aTransport=new Ship("������",23);//��ʾ�ִ�����
		aTransport.run();
		
		aTransport=new Truck("����",80);//��ʾ�ϳ�����
		aTransport.run();
		
		aTransport=new Vehicle("����",70);//��ʾ��������
		aTransport.run();
	}
}
