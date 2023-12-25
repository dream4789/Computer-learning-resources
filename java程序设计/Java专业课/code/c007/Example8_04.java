class LtdGenerics<T extends Number>//�����࣬ʵ������ֻ����Number�����࣬Ltd=Limited
{
	private T arr[];
	
	public LtdGenerics(T arr[])//���췽��
	{
		this.arr=arr;
	}
	public T max()//�������
	{
		T m=arr[0];//�����0��Ԫ�������ֵ
		for(int i=1;i<arr.length;i++)//����ж�
			if(m.doubleValue()<arr[i].doubleValue())
				m=arr[i];//Byte, Double, Float, Integer, Long, Short
					//�Ķ��󶼿��Ե���doubleValue�����õ���Ӧ��˫������
		return m;
	}
	public T min()//����С��
	{
		T m=arr[0];//�����0��Ԫ������Сֵ
		for(int i=1;i<arr.length;i++)//����ж�
			if(m.doubleValue()>arr[i].doubleValue())
				m=arr[i];
		return m;
	}
}
public class Example8_04
{
	public static void main(String[] args)
	{
		//�����������Ķ�������
		Integer integer[]={34,72,340,93,852,37,827,1150,923,48,287,48,25};
		//����������Ķ���
		LtdGenerics<Integer> ltdInt=new LtdGenerics<Integer>(integer);
		System.out.println("���������ֵ��"+ltdInt.max());
		System.out.println("��������Сֵ��"+ltdInt.min());
		
		//����˫�����͵Ķ�������
		Double db[]={34.98,23.7,5.01,78.723,900.5,29.8,34.79,82.,37.48,92.374};
		//����������Ķ���
		LtdGenerics<Double> ltdDou=new LtdGenerics<Double>(db);
		System.out.println("˫�����������ֵ��"+ltdDou.max());
		System.out.println("˫����������Сֵ��"+ltdDou.min());
		
		String str[]={"apple","banana","pear","peach","orange","watermelon"};
		//�������䲻������������Ķ�����ΪString����Number������࣬
		//������ϱ�����䣬�����ܱ���ͨ��
		//LtdGenerics<String> ltdStr=new LtdGenerics<String>(str);
	}
}
