public class Example2_23
{
	public static void main(String args[])
	{
		int x,x1,i;
		int counter=0;/*素数计数器*/
		boolean prime=true;
		
		label://标号
		for(x=101;;x+=2)//无限循环
		{
			prime=true;
			x1=(int)Math.sqrt(x);
			for(i=2;i<=x1;i++)
				if(x%i==0)
				{
					if(i>15)//非素数第1个因子大于15
						break label;//结束外层循环
						//break label所在的循环是内层循环，
						//但结束的是外层循环
					prime=false;
					break;//注意：break所在的循环是内层循环
				}//当break被执行到的时候，结束的是内层循环，
				 //而不是外层循环
			
			if(prime)
			{
				System.out.printf("%4d",x);
				counter++;
				if(counter%5==0)/*输出的每一行素数是5的倍数则换行*/
					System.out.println();
			}
		}
	}
}
