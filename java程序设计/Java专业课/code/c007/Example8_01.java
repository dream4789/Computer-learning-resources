class Basket// 篮子类
{
	int n;// 篮子能放入的物品总数
	int total;// 物品的实际个数
	private Object arr[];// 利用数组盛放物品

	public Basket(int n)// 构造方法
	{
		this.n = n;
		total = 0;
		arr = new Object[n];
	}

	public void add(Object obj)// 将一个对象加到数组中
	{
		arr[total++] = obj;
	}

	public Object indexOf(int i)// 获得数组中第i个元素对象
	{
		return arr[i];
	}

	public int length()// 获得对象中数组的长度
	{
		return total;
	}
}

class Egg {
	double weight;

	public String toString() {
		return ("我是鸡蛋");
	}
}

class Bread {
	double weight;

	public String toString() {
		String s = "我是面包";
		return s;
	}
}

public class Example8_01 {
	public static void main(String[] args) {
		Egg egg[] = new Egg[2];// Egg型对象数组
		egg[0] = new Egg();
		egg[1] = new Egg();
		Basket basket = new Basket(3);// 创建数组类对象

		for (int i = 0; i < egg.length; i++)// 将每个Egg元素加到篮子中
			basket.add(egg[i]);
		basket.add(new Bread());//①混入了一个Bread对象，但编译通过，因为数组类型为Object
		for (int i = 0; i < basket.length(); i++)// 将篮子中的元素值显示出来
		{
			Egg g = (Egg) basket.indexOf(i);// 获得其中第i个元素并强制转换成Egg型
			System.out.println(g); // ②运行时出错了！当i=2时，
			// 对象的实际类型是Bread，
			// 不能强制转换成Egg
		}
	}
}
