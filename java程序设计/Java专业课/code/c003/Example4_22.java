class Company
{
	private String name;//公司名称
	private Employee employee[];//公司雇员
	
	public Company()//构造方法
	{
		name="京东";
		employee=new Employee[2];
		employee[0]=new Employee("张三");
		employee[1]=new Employee("李四");
	}
	public void saleHouses()//销售房屋
	{
		employee[0].buyAHouse(85);
		employee[1].buyAHouse(102);
	}
	public void show()//显示销售情况
	{
		for(int i=0;i<employee.length;i++)
		{
			System.out.print("    "+employee[i].getName()+"买的房屋面积：");
			System.out.println(employee[i].getHouse().houseArea()+"平方米");
		}
	}
	
	class Employee//内部类，雇员类
	{
		private String name;//雇员姓名
		private House house;//雇员购买的房屋
		
		public Employee(String name)
		{
			this.name=name;
		}
		public String getName()
		{
			return name;
		}
		public void buyAHouse(int area)
		{
			house=new House(area);
		}
		public House getHouse()
		{
			return house;
		}
		public int houseArea()
		{
			return house.houseArea();
		}
	}
	
	class House//内部类，房屋类
	{
		private int area;//房屋面积
		
		public House(int area)
		{
			this.area=area;
		}
		public int houseArea()
		{
			return area;
		}
	}
	static class Test//静态嵌套类
	{
		private int value;
		public Test(int value)
		{
			this.value=value;
		}
		public int getValue()
		{
			return value;
		}
	}
}
public class Example4_22
{
	public static void main(String args[])
	{
		Company aCompany=new Company();
		
		aCompany.saleHouses();
		
		System.out.println("房屋销售情况：");
		aCompany.show();
		
		//静态嵌套类可以通过外层类使用
		Company.Test test=new Company.Test(115);
		System.out.println(test.getValue());
		
		//内部类不允许通过外层类使用，如下：
		//Company.House aHouse=new Company.House(101);
	}
}
