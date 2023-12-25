class Company
{
	private String name;//��˾����
	private Employee employee[];//��˾��Ա
	
	public Company()//���췽��
	{
		name="����";
		employee=new Employee[2];
		employee[0]=new Employee("����");
		employee[1]=new Employee("����");
	}
	public void saleHouses()//���۷���
	{
		employee[0].buyAHouse(85);
		employee[1].buyAHouse(102);
	}
	public void show()//��ʾ�������
	{
		for(int i=0;i<employee.length;i++)
		{
			System.out.print("    "+employee[i].getName()+"��ķ��������");
			System.out.println(employee[i].getHouse().houseArea()+"ƽ����");
		}
	}
	
	class Employee//�ڲ��࣬��Ա��
	{
		private String name;//��Ա����
		private House house;//��Ա����ķ���
		
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
	
	class House//�ڲ��࣬������
	{
		private int area;//�������
		
		public House(int area)
		{
			this.area=area;
		}
		public int houseArea()
		{
			return area;
		}
	}
	static class Test//��̬Ƕ����
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
		
		System.out.println("�������������");
		aCompany.show();
		
		//��̬Ƕ�������ͨ�������ʹ��
		Company.Test test=new Company.Test(115);
		System.out.println(test.getValue());
		
		//�ڲ��಻����ͨ�������ʹ�ã����£�
		//Company.House aHouse=new Company.House(101);
	}
}
