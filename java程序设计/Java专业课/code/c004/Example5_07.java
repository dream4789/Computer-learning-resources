class Point implements Cloneable//������Object
{
   //��Ķ���ͬ��5.6
}
public class Example5_07
{
	public static void main(String args[])
	{
		Point point=null;// //�˴�һ��Ҫ��ֵnull
	
		System.out.println(��������point��ʾ����һ���ն�����");
		System.out.println("   \"point instanceof Point\"="+(point instanceof Point));
		System.out.println("   \"point instanceof Object\"="+(point instanceof Object));
		
		System.out.println("������point��ʾ��һ�������Ķ�����");
		point=new Point(10,20);//����Point���Object��Ķ���
		System.out.println("   \"point instanceof Point\"="+(point instanceof Point));
		System.out.println("   \"point instanceof Object\"="+(point instanceof Object));
	}
}
