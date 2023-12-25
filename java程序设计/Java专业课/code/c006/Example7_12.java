package ch7;
import java.util.*;
public class Example7_12
{
	private static int days(int year,int month,int day)
	{
		Calendar start=Calendar.getInstance();//获得日历类的实例
		start.set(2010,1,1,0,0,0);//设置日期和时间
		long milliSec1=start.getTimeInMillis();//对应的毫秒数
		
		Calendar oneDay=Calendar.getInstance();
		oneDay.set(year,month,day,0,0,0);
		long milliSec2=oneDay.getTimeInMillis();
		
		//转换成天数，2010.1.1也算一天，所以加1
		return (int)((milliSec2-milliSec1)/(24*3600*1000))+1;
	}
	private static String whatToDo(int year,int month,int day)
	{
		String doing=null;
		int intervals=days(year,month,day);//获得相隔的天数
		switch(intervals%5)
		{
		case 1:
		case 2:
		case 3:
			doing="打渔";break;
		case 0:
		case 4:
			doing="晒网";
		}
		return doing;
	}
	                                                   
	public static void main(String[] args)
	{
		String dateStr;
		int year=2015,month=1,day=5;
		dateStr=year+"."+month+"."+day;
		System.out.println(dateStr+whatToDo(year,month,day));
		year=2013;month=9;day=11;
		dateStr=year+"."+month+"."+day;
		System.out.println(dateStr+whatToDo(year,month,day));
		year=2010;month=1;day=6;
		dateStr=year+"."+month+"."+day;
		System.out.println(dateStr+whatToDo(year,month,day));
	}
}
