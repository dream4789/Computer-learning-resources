package ch7��
import java.math.BigDecimal;
public class Example7_11{
public static void main(String []args){
        double x1 = 0.6;  //0.6�ڼ�������޷���ȷ��ʾ
        double y1 = 0.1;   //0.1�ڼ�������޷���ȷ��ʾ
        double x2 = 0.5;   //0.5�ڼ�����п��Ծ�ȷ��ʾ
        double y2 = 0.25;  //0.25�ڼ�����п��Ծ�ȷ��ʾ
        BigDecimal a1,a2;
        BigDecimal b1,b2;
        a1 = new BigDecimal(0.6);
        b1 = new BigDecimal(0.1);
        a2 = new BigDecimal(0.5);
        b2 = new BigDecimal(0.25);
        System.out.println(a1.add(b1));
        System.out.println(x1+y1);
        System.out.println(a2.add(b2));
        System.out.println(x2+y2);
}
} 
