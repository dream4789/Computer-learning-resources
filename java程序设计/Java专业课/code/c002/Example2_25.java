public class Example2_25 
{
	public static void main(String args[])
	{
		int i,j;
		
		label://标号
		for(i=1;i<=3;i++)
		{
			for(j=1;i<=50;j++)
			{
				if(i+j>4)
					continue label;//转向外层循环
				
				System.out.println("i:"+i+",j:"+j);
			}
		}
	}
}
