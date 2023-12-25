class Person
{
	public void doing()
	{
		System.out.println("人们正在做......");
	}
}
public class Example5_14
{
	public static void main(String args[])
	{
		Person aPerson=new Person();
		aPerson.doing();
		
		aPerson=new Person()//生成子类对象
		{//定义匿名类，它是Person类的子类
			public void doing()//重写父类中的方法
			{
				System.out.println("学生们正在学习！");
			}
		};//注意，一条语句写在多行，到此结束
		aPerson.doing();//通过父类对象调用子类中的方法，多态性
		
		aPerson=new Person()
		{//再声明匿名类并创建对象
			public void doing()
			{
				System.out.println("环卫工人正在清扫！");
			}
		};
		aPerson.doing();//多态性
	}
}
