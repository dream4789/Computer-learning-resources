class Transport//交通工具类
{
	public void run()
	{
		System.out.println("一个交通工具正在行驶！");
	}
}
class Plane extends Transport//飞机类
{
	@Override//表示下面的方法是对父类方法的重写
	public void planeRun()
	{
		System.out.println("一架飞机正在空中飞行！");
	}
}
public class Example5_10
{
    public static void main(String [] args)
    {
	Plane aPlane=new Plane();
	
	aPlane.planeRun();
    }  
}
