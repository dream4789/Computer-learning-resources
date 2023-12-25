import java.util.Random;

public class Example3_29
{
	public static void main(String args[])
	{
		//������������ά���飬������ͬ��������ͬ
		int a[][]=new int[3][4],b[][]=new int[3][4];
		int result[][]=new int[3][4];
		
		getElements(a);
		getElements(b);
		compute(a,b,result,'+');
		print(a,b,result,'+');
		
		compute(a,b,result,'-');
		print(a,b,result,'-');	
	}
	private static void getElements(int x[][])//������Ԫ�ظ�ֵ�������
	{
		Random rand=new Random();
		
		for(int i=0;i<x.length;i++)
			for(int j=0;j<x[i].length;j++)
				x[i][j]=rand.nextInt(100);
	}
	//ִ�мӻ������
	private static void compute(int a[][],int b[][],int result[][],char oper)
	{
		for(int i=0;i<result.length;i++)
			for(int j=0;j<result[i].length;j++)
				result[i][j]=oper=='+'?a[i][j]+b[i][j]:a[i][j]-b[i][j];
	}
	//��ӡ����
	private static void print(int a[][],int b[][],int result[][],char oper)
	{
		int i;
		
		for(i=0;i<result.length;i++)
		{
			for(int x:a[i])//����ǿ��ѭ��
				System.out.printf("%3d", x);
			System.out.printf("%3c",oper);
			
			//for(j=0;j<b[i].length;j++)//��ͬһ�д�ӡb�ĵ�i��
			for(int x:b[i])
				System.out.printf("%3d", x);
			System.out.printf("%3s","=");

			for(int x:result[i])//��ͬһ�д�ӡresult�ĵ�i��
				System.out.printf("%4d", x);
			System.out.println();//��һ���д�ӡ�����i+1��
		}
		System.out.println();
	}
}
