interface Charge//接口声明
{
	public void 收费();//抽象方法
}
class Cinema implements Charge//电影院类，实现接口
{
	public void 收费()
	{
		System.out.println("电影票10元一张。");
	}
}
class Taxi implements Charge//出租车类，实现接口
{
	public void 收费()
	{
		System.out.println("出租车基价9.9元");
	}
}
class Highway implements Charge//高速公路类，实现接口
{
	public void 收费()
	{
		System.out.println("高速公路收费25.0元");
	}
}
class Mountainimplements Charge//山类，实现接口
{
	public void 收费()
	{
		System.out.println("黄山门票120元");
	}
}
public classExample5_18
{
	public static void main(String args[])
	{
		Charge charge;//声明接口变量
		
		charge=new Cinema();//接口变量表示电影院对象
		charge.收费();//多态性
		
		charge=new Taxi();//接口变量表示出租车对象
		charge.收费();//多态性
		
		charge=new Highway();//接口变量表示高速公路对象
		charge.收费();//多态性
		
		charge=new Mountain();//接口变量表示黄山对象
		charge.收费();//多态性		
	}
}
