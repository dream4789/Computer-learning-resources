class Basket// ������
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

	public void add(Object obj)// ��һ������ӵ�������
	{
		arr[total++] = obj;
	}

	public Object indexOf(int i)// ��������е�i��Ԫ�ض���
	{
		return arr[i];
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

public class Example8_01 {
	public static void main(String[] args) {
		Egg egg[] = new Egg[2];// Egg�Ͷ�������
		egg[0] = new Egg();
		egg[1] = new Egg();
		Basket basket = new Basket(3);// �������������

		for (int i = 0; i < egg.length; i++)// ��ÿ��EggԪ�ؼӵ�������
			basket.add(egg[i]);
		basket.add(new Bread());//�ٻ�����һ��Bread���󣬵�����ͨ������Ϊ��������ΪObject
		for (int i = 0; i < basket.length(); i++)// �������е�Ԫ��ֵ��ʾ����
		{
			Egg g = (Egg) basket.indexOf(i);// ������е�i��Ԫ�ز�ǿ��ת����Egg��
			System.out.println(g); // ������ʱ�����ˣ���i=2ʱ��
			// �����ʵ��������Bread��
			// ����ǿ��ת����Egg
		}
	}
}
