class Transport//��ͨ������
{
	public void run()
	{
		System.out.println("һ����ͨ����������ʻ��");
	}
}
class Plane extends Transport//�ɻ���
{
	@Override//��ʾ����ķ����ǶԸ��෽������д
	public void planeRun()
	{
		System.out.println("һ�ܷɻ����ڿ��з��У�");
	}
}
public class Example5_10
{
    public static void main(String [] args)
    {
	Plane aPlane=new Plane();
	
	aPlane.planeRun();
    }  
}
