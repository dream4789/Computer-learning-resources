class Example3_2
{  
    public static void main(String args[])
    {
      char a[]={'金','木','水','火','土'};
      char secret='z';
      for(int i=0;i<a.length;i++)
      {
         a[i]=(char)(a[i]^secret);
      } 
      System.out.printf("密文:\n");
      for(int i=0;i<a.length;i++)
       {
         System.out.printf("%3c",a[i]);   
       }
       
      for(int i=0;i<a.length;i++)
      {
         a[i]=(char)(a[i]^secret);
      } 
      System.out.printf("\n原文:\n");
      for(int i=0;i<a.length;i++)
       {
         System.out.printf("%3c",a[i]);   
       }
    }
}
