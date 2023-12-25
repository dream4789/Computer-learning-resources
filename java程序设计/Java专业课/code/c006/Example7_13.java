package ch7;
import java.util.*;
import java.time.LocalTime;
import java.time.temporal.ChronoUnit;
public class Example7_13 
{
	public static void main(String[] args)
	{
        LocalTime localTime1 = LocalTime.now();    //新建LocalTime实例
        LocalTime localTime2 = LocalTime.now().withNano(0);//0为去除时间中毫秒字段
        System.out.println(localTime1);
        System.out.println(localTime2);
       //Get the hour of the day
       System.out.println("The hour of the day:: " + localTime1.getHour());
       //时间中小时数加2，chronoUnit是计时单位的意思
       System.out.println(localTime1.plus(2, ChronoUnit.HOURS));
       //时间中分钟数加6
       System.out.println(localTime1.plusMinutes(6));
       //时间中秒数加30
       System.out.println(localTime1.plusSeconds(30));
       //时间中小时数减2
       System.out.println(localTime1.minus(2, ChronoUnit.HOURS));
    }
}
