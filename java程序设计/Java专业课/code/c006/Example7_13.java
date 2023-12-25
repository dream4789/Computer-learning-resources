package ch7;
import java.util.*;
import java.time.LocalTime;
import java.time.temporal.ChronoUnit;
public class Example7_13 
{
	public static void main(String[] args)
	{
        LocalTime localTime1 = LocalTime.now();    //�½�LocalTimeʵ��
        LocalTime localTime2 = LocalTime.now().withNano(0);//0Ϊȥ��ʱ���к����ֶ�
        System.out.println(localTime1);
        System.out.println(localTime2);
       //Get the hour of the day
       System.out.println("The hour of the day:: " + localTime1.getHour());
       //ʱ����Сʱ����2��chronoUnit�Ǽ�ʱ��λ����˼
       System.out.println(localTime1.plus(2, ChronoUnit.HOURS));
       //ʱ���з�������6
       System.out.println(localTime1.plusMinutes(6));
       //ʱ����������30
       System.out.println(localTime1.plusSeconds(30));
       //ʱ����Сʱ����2
       System.out.println(localTime1.minus(2, ChronoUnit.HOURS));
    }
}
