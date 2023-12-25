public class Example3_5
{  
    public static void main (String args[ ])
    {
       double sum=0,item=1;
       int i=1;
       while(i<=1000)
       {
         sum=sum+item;
         i++;
         item=item*(1.0/i);   
       }
      sum=sum+1;
      System.out.println("e="+sum);
      sum=0;
      i=1;
      item=1;
      do
        {
         sum=sum+item;
         i++;
         item=item*(1.0/i) ;
        }
      while(i<=1000);
      sum=sum+1;
      System.out.println("e="+sum);   
    }
}
