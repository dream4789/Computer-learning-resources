public class Example3_6
{  
    public static void main (String args[ ])
    {
        int sum,i,j;
        for(i=1;i<=1000;i++)
        {
            for(j=1,sum=0;j<=i/2;j++)
            {
              if(i%j==0)
               {
                  sum=sum+j;
               }
            } 
           if(sum==i)
            {
              System.out.printf("%8d是一个完数%n",i);
            }
        }       
    }  
}
