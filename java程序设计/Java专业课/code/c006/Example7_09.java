package ch7;
import java.text.* ;  
public class Example7_09
{  
	public static void main(String[] args)
	{  
		format("###,###.###",111222.34567);
		format("000,000.000",11222.34567);
		format("###,###.###��",111222.34567);
		format("000,000.000��",11222.34567);
		format("##.###%",0.345678);
		format("00.###%",0.0345678);
		format("###.###\u2030",0.345678);
	}
	private static void format(String pattern,double value)//��ʽ������
	{
		DecimalFormat df = null;// ����һ��DecimalFormat��Ķ���  
		df = new DecimalFormat(pattern);// ʵ�������󣬴���ģ��  
		String str = df.format(value);//��ʽ������  
		System.out.println("ʹ��"+pattern+"��ʽ������"+value+"��"+str) ;  
	}
}
