class Transport//交通工具类
{
	int speed;
	String name;
	public Transport(){}//构造方法
	public Transport(String name,int speed)//构造方法
	{
		this.speed=speed;
		this.name=name;
	}
	public void run()//交通工具运行
	{
		System.out.println("交通工具在运行！");
	}
}
class Plane extends Transport//飞机子类
{
	public Plane(String name,int speed)//构造方法
	{
		super(name,speed);//调用父类构造方法
	}
	public void run()//重写父类方法
	{
		System.out.println(name+"飞机以"+speed+"km/h的速度在空中飞行。");
	}	
}
class Ship extends Transport//轮船子类
{
	public Ship(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//重写父类方法
	{
		System.out.println(name+"轮船以"+speed+"节的速度在水中航行。");
	}
}
class Rocket extends Transport//火箭子类
{
	public Rocket(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//重写父类方法
	{
		System.out.println(name+"火箭以"+speed+"km/h的速度在太空中穿行。");
	}	
}
class Vehicle extends Transport//汽车子类
{
	public Vehicle(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//重写父类方法
	{
		System.out.println(name+"汽车以"+speed+"km/h的公路上行驶。");		
	}
}
class Car extends Vehicle//汽车类派生小轿车子类
{
	public Car(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//重写父类方法
	{
		System.out.println(name+"轿车以"+speed+"km/h的速度在公路上飞驰。");		
	}
}
class Truck extends Vehicle//汽车类派生卡车子类
{
	public Truck(String name,int speed)
	{
		super(name,speed);
	}
	public void run()//重写父类方法
	{
		System.out.println(name+"卡车以"+speed+"km/h的公路上行驶。");
	}
}
public class Example5_13
{
	public static void main(String args[])
	{
		Transport aTransport;//声明一个交通工具类的对象
		
		aTransport=new Rocket("长征4号",2200);//赋值兼容规则，表示火箭对象
		aTransport.run();//调用run方法
		
		aTransport=new Car("红旗",120);//表示轿车对象
		aTransport.run();
		
		aTransport=new Plane("空客A320",800);//表示飞机对象
		aTransport.run();
		
		aTransport=new Ship("辽宁舰",23);//表示轮船对象
		aTransport.run();
		
		aTransport=new Truck("东风",80);//表示上车对象
		aTransport.run();
		
		aTransport=new Vehicle("金龙",70);//表示汽车对象
		aTransport.run();
	}
}
