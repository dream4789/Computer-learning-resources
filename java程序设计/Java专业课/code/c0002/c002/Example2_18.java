public class Example2_18
{
	public static void main(String args[])
	{
		int sum,i;

		//sum和i都在变量初始化表达式中初始化		
		for(sum=0,i=1;i<=100;i++)
			sum=sum+i;
		
		System.out.println("sum="+sum);
	}
}
