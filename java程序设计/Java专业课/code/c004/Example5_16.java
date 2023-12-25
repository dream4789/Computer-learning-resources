abstract class Transport//抽象的交通工具类
{
	int speed;
	String name;
	public Transport(){}//构造方法
	public Transport(String name,int speed)//构造方法
	{
		this.speed=speed;
		this.name=name;
	}
	public abstract void run();//抽象方法
}
//其它子类定义同例5.13
public class Example5_16
{
	public static void main(String args[])
	{
		Transport aTransport;//声明一个交通工具类的对象
		
		//aTransport=new Transport();不允许，因为Transport是一个抽象类
		
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
