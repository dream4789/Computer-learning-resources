class Basket<T>// 篮子类
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

	public void add(T obj)// 将一个T型对象加到数组中
	{
		arr[total++] = obj;
	}

	public T indexOf(int i)// 获得数组中第i个元素对象
	{
		return (T) arr[i];//将元素强制转换成T型。
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

public class Example8_02 {
	public static void main(String[] args) {
		Egg egg[] = new Egg[2];// String型对象数组
		egg[0] = new Egg();
		egg[1] = new Egg();
		Basket<Egg> basket = new Basket<Egg>(3);// //创建一个泛型类对象，所有元素均为Egg型

		for (int i = 0; i < egg.length; i++)// 将每个元素加到篮子对象中
			basket.add(egg[i]);
		basket.add(new Bread());//编译不通过，因为不是Egg类型
		for (int i = 0; i < basket.length(); i++)// 将篮子中的元素值显示出来
		{
			Egg g =  basket.indexOf(i);// 获得其中第i个元素，不用强制转换成Egg型
			System.out.println(g);
		}
	}
}
