class Example3_7
{  
    public static void main(String args[]) 
    { 
       int sum=0,i,j;
       for( i=1;i<=10;i++)      //¸ÃÑ­»·¼ÆËã3+6+9¡£
       {  
         if(i%3!=0) 
          {
             continue;  
          } 
          else
          {
          } 
          sum=sum+i;
       }
       System.out.println("sum="+sum);
    }
}
