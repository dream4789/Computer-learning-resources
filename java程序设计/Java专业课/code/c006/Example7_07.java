package ch7;
import java.math.*;
public class Example7_07
{
	public static void main(String[] args)
	{
		BigInteger sum = new BigInteger("0"),
				item = new BigInteger("1"),
				ONE = new BigInteger("1"),
				i = ONE,
				n = new BigInteger("30");
		while(i.compareTo(n)<=0)//�����������Ƚϴ�С
		{
			//��ǰ��item=i!�ۼӵ�sum��
			sum = sum.add(item);
			i = i.add(ONE);//i����1
			//item���(i+1)!
			item = item.multiply(i);
		}                                
		System.out.println("sum= "+sum.toString());
	}
}
