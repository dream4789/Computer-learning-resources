class Basket<T>// ������
{
	int n;// �����ܷ������Ʒ����
	int total;// ��Ʒ��ʵ�ʸ���
	private Object arr[];// ��������ʢ����Ʒ

	public Basket(int n)// ���췽��
	{
		this.n = n;
		total = 0;
		arr = new Object[n];
	}

	public void add(T obj)// ��һ��T�Ͷ���ӵ�������
	{
		arr[total++] = obj;
	}

	public T indexOf(int i)// ��������е�i��Ԫ�ض���
	{
		return (T) arr[i];//��Ԫ��ǿ��ת����T�͡�
	}

	public int length()// ��ö���������ĳ���
	{
		return total;
	}
}

class Egg {
	double weight;

	public String toString() {
		return ("���Ǽ���");
	}
}

class Bread {
	double weight;

	public String toString() {
		String s = "�������";
		return s;
	}
}

public class Example8_02 {
	public static void main(String[] args) {
		Egg egg[] = new Egg[2];// String�Ͷ�������
		egg[0] = new Egg();
		egg[1] = new Egg();
		Basket<Egg> basket = new Basket<Egg>(3);// //����һ���������������Ԫ�ؾ�ΪEgg��

		for (int i = 0; i < egg.length; i++)// ��ÿ��Ԫ�ؼӵ����Ӷ�����
			basket.add(egg[i]);
		basket.add(new Bread());//���벻ͨ������Ϊ����Egg����
		for (int i = 0; i < basket.length(); i++)// �������е�Ԫ��ֵ��ʾ����
		{
			Egg g =  basket.indexOf(i);// ������е�i��Ԫ�أ�����ǿ��ת����Egg��
			System.out.println(g);
		}
	}
}
