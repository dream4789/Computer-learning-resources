package ch7;
import java.text.*;
import java.util.Random;
public class Example7_08
{
	public static void main(String[] args)
	{
		Random random=new Random();
		NumberFormat nf = null ; // 声明一个NumberFormat对象  
		nf = NumberFormat.getInstance() ; // 得到默认的数字格式化显示 
		
		int i=random.nextInt(20000000);//得到[0,20000000)之间的一个随机整数
		long l=random.nextLong();//产生一个随机长整数
		double d1=Math.random()*3000000;//得到[0,300000)之间的一个随机浮点数
		double d2=random.nextDouble()*12000;//得到[0,12000)间的一个随机浮点数
		
		System.out.println(i+"格式化后："+nf.format(i));
		System.out.println(l+"格式化后："+nf.format(l));
		System.out.println(d1+"格式化后："+nf.format(d1));
		System.out.println(d2+"格式化后："+nf.format(d2));
	}
}
