public class Example2_22
{
	public static void main(String args[])
	{
		long sum=0;//��ʾ��ֵ�����ܱȽϴ�
		int item=1,i=1;//item��ʾÿһ���׳�
		
		while(true)//���ޣ�����ѭ��
		{
			sum=sum+item;//��һ���׳��ۼӵ�sum��
			
			System.out.print(i+"!");//���i!
			
			i++;//��һ����
			item=item*i;//��һ�����Ľ׳�
			
			if(item<=1000_0000)
				System.out.print("+");
			else
				break;//ʹ����ѭ������
		}
		System.out.printf("=%,d\n",sum);
	}
}
