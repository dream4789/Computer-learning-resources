public class Example2_25 
{
	public static void main(String args[])
	{
		int i,j;
		
		label://���
		for(i=1;i<=3;i++)
		{
			for(j=1;i<=50;j++)
			{
				if(i+j>4)
					continue label;//ת�����ѭ��
				
				System.out.println("i:"+i+",j:"+j);
			}
		}
	}
}
