import java.util.Scanner;

public class Example4_03
{
	public static void main(String args[])
	{
		int n;
		Scanner reader=new Scanner(System.in);
		
		System.out.print("����һ����������");
		n=reader.nextInt();
		
		System.out.println("1��"+n+"�ĺ�ֵ��"+sum(n));
	}
	private static int sum(int n)//�ݹ鷽��
	{
		if(n>1)
			return sum(n-1)+n;//ֱ�ӵ�������
		else
			return 1;
	}
}
