import java.util.*;
public class Example3_4
{  
    public static void main (String args[ ])
    {
       Scanner reader=new Scanner(System.in);
       System.out.println("输入一个月份:");
       int n=reader.nextInt();
       switch(n)
        {
         case 1 :
         case 2 :
         case 3 :
                System.out.printf("%d月属于第一季度",n);   
                break;    
         case 4 :
         case 5 :
         case 6 :
                System.out.printf("%d月属于第二季度",n);   
                break; 
         case 7 :
         case 8 :
         case 9 :
                System.out.printf("%d月属于第三季度",n);   
                break; 
         case 10 :
         case 11 :
         case 12 :
                System.out.printf("%d月属于第四季度",n);   
                break; 
         default:  
                System.out.printf("%d不代表月份",n);  
        }
    }
}
