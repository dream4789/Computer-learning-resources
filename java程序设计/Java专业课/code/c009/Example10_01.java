package ch10;
class ExtThread extends Thread//����Thread�������߳�����
{
	public ExtThread(String name)//���췽���������趨�߳��ַ�������
	{
		super(name);//���ø��๹�췽�������߳���
	} 
	public void run() 
	{
		for(int i = 0;i<=4;i++)//ÿ���߳�ѭ��4��
		{
			for(long k= 0; k <100000000;k++);//��ʱ
			//����߳�������ִ�д���
			System.out.println(this.getName()+" :"+i);
		}
	} 
}
public class Example10_01
{
	public static void main(String[] args)
	{
		//�����̶߳���t1�����ַ�������ΪA
		Thread t1 = new ExtThread("A"); 
		Thread t2 = new ExtThread("B"); 
		t1.start();//����start()����ʹ�̴߳��ڿ�����״̬
		t2.start(); 
	}
}
