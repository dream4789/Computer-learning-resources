package ch7;
import java.time.Instant;
import java.time.LocalDate;
import java.time.ZoneId;
import java.time.chrono.ChronoZonedDateTime;
import java.util.Date;
public class Example7_14 {
public static LocalDate DateToLocaleDate(Date date) {
      Instant  instant = date.toInstant();        //时间实例
      ZoneId zoneId  = ZoneId.systemDefault();  //时区id
      return instant.atZone(zoneId).toLocalDate();  //本地格式的日期
}
public static Date LocalDateToDate(LocalDate localDate) {
      ZoneId zoneId = ZoneId.systemDefault();      
      ChronoZonedDateTime<LocalDate> zonedDateTime = localDate.atStartOfDay(zoneId);
      return Date.from(zonedDateTime.toInstant());    //CST标准格式日期
}
public static void main(String[] args) {
      System.out.println(DateToLocaleDate(new Date()));
      System.out.println(LocalDateToDate(LocalDate.now()));
}
}
