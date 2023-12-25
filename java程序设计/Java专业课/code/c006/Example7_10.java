package ch7;
import java.util.Date;
import java.util.Formatter; 
public class Example7_10
{ 
	public static void main(String[] args) 
	{
		Formatter formatter =new Formatter(System.out);//注意参数
		//格式化输出字符串和数字,%是引导格式串符号
		//-: 指定为左对齐，默认右对齐 
		//10：输出域宽为10,实际数字占不满则输出空格，若超过则全部输出 
		//.6：在此表示输出参数6的最大字符数量，如果是浮点数字，则表示
		//小数部分显示的位数 
		//s：表示输入参数是字符串，1$：取第一个参数，即123
		System.out.println("数字输出格式化：");
		formatter.format("%1$2s %2$10.6s\n", "123", "456.678");
		System.out.println("-----------------------");
		
		Date date = new Date();
		System.out.println("当前日期："+date);
		//日期的格式化，并将格式化结果存储到一个字符串变量中
		//1$：取第一个参数，即date，t日期，Y，m，e分别为年、月、日
		String s = String.format("当前日期格式化:%1$tY-%1$tm-%1$te", date);
		System.out.println(s);
		System.out.println("-----------------------");
		
		//将格式化的结果存储到字符串
		String fs = String.format("当日开销(%.2f,%d)", 173.278, 65);
		System.out.println(fs);
	} 
}
