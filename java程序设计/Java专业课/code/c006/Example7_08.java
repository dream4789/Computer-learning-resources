package ch7;
import java.text.*;
import java.util.Random;
public class Example7_08
{
	public static void main(String[] args)
	{
		Random random=new Random();
		NumberFormat nf = null ; // ����һ��NumberFormat����  
		nf = NumberFormat.getInstance() ; // �õ�Ĭ�ϵ����ָ�ʽ����ʾ 
		
		int i=random.nextInt(20000000);//�õ�[0,20000000)֮���һ���������
		long l=random.nextLong();//����һ�����������
		double d1=Math.random()*3000000;//�õ�[0,300000)֮���һ�����������
		double d2=random.nextDouble()*12000;//�õ�[0,12000)���һ�����������
		
		System.out.println(i+"��ʽ����"+nf.format(i));
		System.out.println(l+"��ʽ����"+nf.format(l));
		System.out.println(d1+"��ʽ����"+nf.format(d1));
		System.out.println(d2+"��ʽ����"+nf.format(d2));
	}
}
