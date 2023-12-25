class Point implements Cloneable//父类是Object
{
   //类的定义同例5.6
}
public class Example5_07
{
	public static void main(String args[])
	{
		Point point=null;// //此处一定要赋值null
	
		System.out.println(“对象名point表示的是一个空对象，则：");
		System.out.println("   \"point instanceof Point\"="+(point instanceof Point));
		System.out.println("   \"point instanceof Object\"="+(point instanceof Object));
		
		System.out.println("对象名point表示了一个真正的对象，则：");
		point=new Point(10,20);//它是Point类和Object类的对象
		System.out.println("   \"point instanceof Point\"="+(point instanceof Point));
		System.out.println("   \"point instanceof Object\"="+(point instanceof Object));
	}
}
