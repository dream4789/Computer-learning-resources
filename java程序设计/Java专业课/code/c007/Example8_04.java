class LtdGenerics<T extends Number>//泛型类，实际类型只能是Number的子类，Ltd=Limited
{
	private T arr[];
	
	public LtdGenerics(T arr[])//构造方法
	{
		this.arr=arr;
	}
	public T max()//找最大数
	{
		T m=arr[0];//假设第0个元素是最大值
		for(int i=1;i<arr.length;i++)//逐个判断
			if(m.doubleValue()<arr[i].doubleValue())
				m=arr[i];//Byte, Double, Float, Integer, Long, Short
					//的对象都可以调用doubleValue方法得到对应的双精度数
		return m;
	}
	public T min()//找最小数
	{
		T m=arr[0];//假设第0个元素是最小值
		for(int i=1;i<arr.length;i++)//逐个判断
			if(m.doubleValue()>arr[i].doubleValue())
				m=arr[i];
		return m;
	}
}
public class Example8_04
{
	public static void main(String[] args)
	{
		//定义整型数的对象数组
		Integer integer[]={34,72,340,93,852,37,827,1150,923,48,287,48,25};
		//创建泛型类的对象
		LtdGenerics<Integer> ltdInt=new LtdGenerics<Integer>(integer);
		System.out.println("整型数最大值："+ltdInt.max());
		System.out.println("整型数最小值："+ltdInt.min());
		
		//定义双精度型的对象数组
		Double db[]={34.98,23.7,5.01,78.723,900.5,29.8,34.79,82.,37.48,92.374};
		//创建泛型类的对象
		LtdGenerics<Double> ltdDou=new LtdGenerics<Double>(db);
		System.out.println("双精度型数最大值："+ltdDou.max());
		System.out.println("双精度型数最小值："+ltdDou.min());
		
		String str[]={"apple","banana","pear","peach","orange","watermelon"};
		//下面的语句不允许创建泛型类的对象，因为String不是Number类的子类，
		//如果加上本条语句，程序不能编译通过
		//LtdGenerics<String> ltdStr=new LtdGenerics<String>(str);
	}
}
