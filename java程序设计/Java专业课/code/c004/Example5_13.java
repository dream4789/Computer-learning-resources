class Transport//��ͨ������
{
	int speed;
	String name;
	public Transport(){}//���췽��
	public Transport(String name,int speed)//���췽��
	{
		this.speed=speed;
		this.name=name;
	}
	public void run()//��ͨ��������
	{
		System.out.println("��ͨ���������У�");
	}
}
class Plane extends Transport//�ɻ�����
{
	public Plane(String name,int speed)//���췽��
	{
		super(name,speed);//���ø��๹�췽��
	}
	public void run()//��д���෽��
	{
		System.out.println(name+"�ɻ���"+speed+"km/h���ٶ��ڿ��з��С�");
	}	
}
class Ship extends Transport//�ִ�����
{
	public Ship(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//��д���෽��
	{
		System.out.println(name+"�ִ���"+speed+"�ڵ��ٶ���ˮ�к��С�");
	}
}
class Rocket extends Transport//�������
{
	public Rocket(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//��д���෽��
	{
		System.out.println(name+"�����"+speed+"km/h���ٶ���̫���д��С�");
	}	
}
class Vehicle extends Transport//��������
{
	public Vehicle(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//��д���෽��
	{
		System.out.println(name+"������"+speed+"km/h�Ĺ�·����ʻ��");		
	}
}
class Car extends Vehicle//����������С�γ�����
{
	public Car(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//��д���෽��
	{
		System.out.println(name+"�γ���"+speed+"km/h���ٶ��ڹ�·�Ϸɳۡ�");		
	}
}
class Truck extends Vehicle//������������������
{
	public Truck(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//��д���෽��
	{
		System.out.println(name+"������"+speed+"km/h�Ĺ�·����ʻ��");
	}
}
public class Example5_13
{
	public static void main(String args[])
	{
		Transport aTransport;//����һ����ͨ������Ķ���
		
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
