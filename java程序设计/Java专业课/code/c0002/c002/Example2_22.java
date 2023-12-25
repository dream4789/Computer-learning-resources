public class Example2_22
{
	public static void main(String args[])
	{
		long sum=0;//表示和值，可能比较大
		int item=1,i=1;//item表示每一个阶乘
		
		while(true)//无限（死）循环
		{
			sum=sum+item;//将一个阶乘累加到sum中
			
			System.out.print(i+"!");//输出i!
			
			i++;//下一个数
			item=item*i;//下一个数的阶乘
			
			if(item<=1000_0000)
				System.out.print("+");
			else
				break;//使无限循环结束
		}
		System.out.printf("=%,d\n",sum);
	}
}
