package ch7;
import java.util.Objects;
public class Example7_20{
    public static void main(String[] args) { 
        String str1 = null£»
        String str2 = null£»
        System.out.println(Objects.equals(str1£¬str2));   //true
        System.out.println(str1.equals(str2));           //null pointer exception
    } 
}
