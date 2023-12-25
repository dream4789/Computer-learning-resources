package ch7;
import java.time.Instant;
import java.time.LocalDate;
import java.time.ZoneId;
import java.time.chrono.ChronoZonedDateTime;
import java.util.Date;
public class Example7_14 {
public static LocalDate DateToLocaleDate(Date date) {
      Instant  instant = date.toInstant();        //ʱ��ʵ��
      ZoneId zoneId  = ZoneId.systemDefault();  //ʱ��id
      return instant.atZone(zoneId).toLocalDate();  //���ظ�ʽ������
}
public static Date LocalDateToDate(LocalDate localDate) {
      ZoneId zoneId = ZoneId.systemDefault();      
      ChronoZonedDateTime<LocalDate> zonedDateTime = localDate.atStartOfDay(zoneId);
      return Date.from(zonedDateTime.toInstant());    //CST��׼��ʽ����
}
public static void main(String[] args) {
      System.out.println(DateToLocaleDate(new Date()));
      System.out.println(LocalDateToDate(LocalDate.now()));
}
}
