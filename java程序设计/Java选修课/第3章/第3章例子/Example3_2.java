class Example3_2
{  
    public static void main(String args[])
    {
      char a[]={'��','ľ','ˮ','��','��'};
      char secret='z';
      for(int i=0;i<a.length;i++)
      {
         a[i]=(char)(a[i]^secret);
      } 
      System.out.printf("����:\n");
      for(int i=0;i<a.length;i++)
       {
         System.out.printf("%3c",a[i]);   
       }
       
      for(int i=0;i<a.length;i++)
      {
         a[i]=(char)(a[i]^secret);
      } 
      System.out.printf("\nԭ��:\n");
      for(int i=0;i<a.length;i++)
       {
         System.out.printf("%3c",a[i]);   
       }
    }
}
