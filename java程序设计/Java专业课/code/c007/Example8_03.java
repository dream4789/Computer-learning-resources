public class Example8_03
{
	static <T> void print(T...ts)//���ͷ������β��ǿɱ����
	{
		for(int i=0;i<ts.length;i++)//�����β�������ÿһ��Ԫ��
			System.out.print(ts[i]+" ");
		
		System.out.println();
	}
	public static void main(String[] args)
	{
		print("������","����","̩ɽ");//3��ʵ�ʲ���������һ��
		print("����ֻ�","�۸�",2000.00,"Ԫ");//4��ʵ�ʲ��������Ͳ�һ��
		String fruit[]={"apple","banana","orange","peach","pear"};//String��������
		print(fruit);//1������
	}
}
