public class Example2_23
{
	public static void main(String args[])
	{
		int x,x1,i;
		int counter=0;/*����������*/
		boolean prime=true;
		
		label://���
		for(x=101;;x+=2)//����ѭ��
		{
			prime=true;
			x1=(int)Math.sqrt(x);
			for(i=2;i<=x1;i++)
				if(x%i==0)
				{
					if(i>15)//��������1�����Ӵ���15
						break label;//�������ѭ��
						//break label���ڵ�ѭ�����ڲ�ѭ����
						//�������������ѭ��
					prime=false;
					break;//ע�⣺break���ڵ�ѭ�����ڲ�ѭ��
				}//��break��ִ�е���ʱ�򣬽��������ڲ�ѭ����
				 //���������ѭ��
			
			if(prime)
			{
				System.out.printf("%4d",x);
				counter++;
				if(counter%5==0)/*�����ÿһ��������5�ı�������*/
					System.out.println();
			}
		}
	}
}
