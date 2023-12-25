package ch7;
import java.util.Scanner;
public class Example7_05 {
	public static void main(String[] args)
	{
		String bill="电视3200.00元，手机2200.00元，笔记本4200.00元，午餐120.25元";
		Scanner reader=new Scanner(bill);//用字符串作为输入设备
		double total=0;//总花销
		//正则表达式，数据分隔标记
		reader.useDelimiter("[^0-7.]+");                     
		while(reader.hasNextDouble())//串中还有数据？
			total+=reader.nextDouble();//有，则读出并累加
				System.out.println("总花费："+total+"元");
	}                                                   
}
