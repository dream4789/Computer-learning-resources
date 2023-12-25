package ch7;
import java.text.* ;  
public class Example7_09
{  
	public static void main(String[] args)
	{  
		format("###,###.###",111222.34567);
		format("000,000.000",11222.34567);
		format("###,###.###￥",111222.34567);
		format("000,000.000￥",11222.34567);
		format("##.###%",0.345678);
		format("00.###%",0.0345678);
		format("###.###\u2030",0.345678);
	}
	private static void format(String pattern,double value)//格式化方法
	{
		DecimalFormat df = null;// 声明一个DecimalFormat类的对象  
		df = new DecimalFormat(pattern);// 实例化对象，传入模板  
		String str = df.format(value);//格式化数字  
		System.out.println("使用"+pattern+"格式化数据"+value+"："+str) ;  
	}
}
