import java.util.Random;

public class Example3_29
{
	public static void main(String args[])
	{
		//声明并创建二维数组，行数相同，列数相同
		int a[][]=new int[3][4],b[][]=new int[3][4];
		int result[][]=new int[3][4];
		
		getElements(a);
		getElements(b);
		compute(a,b,result,'+');
		print(a,b,result,'+');
		
		compute(a,b,result,'-');
		print(a,b,result,'-');	
	}
	private static void getElements(int x[][])//给数组元素赋值（随机）
	{
		Random rand=new Random();
		
		for(int i=0;i<x.length;i++)
			for(int j=0;j<x[i].length;j++)
				x[i][j]=rand.nextInt(100);
	}
	//执行加或减运算
	private static void compute(int a[][],int b[][],int result[][],char oper)
	{
		for(int i=0;i<result.length;i++)
			for(int j=0;j<result[i].length;j++)
				result[i][j]=oper=='+'?a[i][j]+b[i][j]:a[i][j]-b[i][j];
	}
	//打印矩阵
	private static void print(int a[][],int b[][],int result[][],char oper)
	{
		int i;
		
		for(i=0;i<result.length;i++)
		{
			for(int x:a[i])//用增强型循环
				System.out.printf("%3d", x);
			System.out.printf("%3c",oper);
			
			//for(j=0;j<b[i].length;j++)//在同一行打印b的第i行
			for(int x:b[i])
				System.out.printf("%3d", x);
			System.out.printf("%3s","=");

			for(int x:result[i])//在同一行打印result的第i行
				System.out.printf("%4d", x);
			System.out.println();//在一下行打印数组第i+1行
		}
		System.out.println();
	}
}
