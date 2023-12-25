public class Example8_03
{
	static <T> void print(T...ts)//泛型方法，形参是可变参数
	{
		for(int i=0;i<ts.length;i++)//访问形参数组中每一个元素
			System.out.print(ts[i]+" ");
		
		System.out.println();
	}
	public static void main(String[] args)
	{
		print("北京市","长江","泰山");//3个实际参数，类型一样
		print("这个手机","价格",2000.00,"元");//4个实际参数，类型不一样
		String fruit[]={"apple","banana","orange","peach","pear"};//String对象数组
		print(fruit);//1个参数
	}
}
