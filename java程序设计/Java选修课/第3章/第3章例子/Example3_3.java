import java.util.*;
public class Example3_3
{  
    public static void main (String args[ ])
    {
        Scanner reader=new Scanner(System.in);
        double a=0,b=0,c=0;
        System.out.println("输入边a:");
        a=reader.nextDouble();
        System.out.println("输入边b:");
        b=reader.nextDouble();
        System.out.println("输入边c:");
        c=reader.nextDouble();
        if(a+b>c&&a+c>b&&b+c>a)
        {
            if(a*a==b*b+c*c||b*b==a*a+c*c||c*c==a*a+b*b)
            {
                System.out.printf("\n%-8.3f%-8.3f%-8.3f构成是直角三角形",a,b,c);
            }
          else if(a*a<b*b+c*c&&b*b<a*a+c*c&&c*c<a*a+b*b)
            {
                System.out.printf("\n%-8.3f%-8.3f%-8.3f构成锐角三角形",a,b,c);
            }
           else
            {
                System.out.printf("\n%-8.3f%-8.3f%-8.3f构成钝角三角形",a,b,c);
            }
        } 
       else
        {
           System.out.printf("%f,%f,%f不能构成三角形",a,b,c); 
        }    
    }
}
