�ڰ�classeslib�зֱ𴴽����������ļ�MyMath.java��MyArray.java��
����MyMath.java��
package classeslib;

import static java.lang.Math.sqrt;//ֻ����Math���еľ�̬����sqrt

public class MyMath
{
	public static boolean isPrime(int x)//��̬�������ж�һ������������
	{
		if(x<=1)
			return false;
		
		int y=(int)sqrt(x);//Math�е�sqrt
		
		for(int i=2;i<=y;i++)
			if(x%i==0)
				return false;
		
		return true;		
	}
}
����MyArray.java��
package classeslib;

import static java.lang.System.out;//ֻ����System.���еľ�̬��out

public class MyArray
{
	public static void print(int a[])//��̬��������ӡһ����������
	{
		for(int x:a)
			out.print(" "+x);//System�е�out
		out.println();//System�е�out
	}
}
���ڰ�classeslib����һ�����д��������ļ�Example4_24.java��
import static java.lang.System.*;//����System�е����о�̬��Ա
import static java.lang.Math.PI;//ֻ����Math���еľ�̬��PI
import static java.util.Arrays.sort;//ֻ����Arrays���еľ�̬����sort

import java.util.Scanner;

//�����Զ��������
import static classeslib.MyArray.*;//����MyArray���е����о�̬��Ա
import static classeslib.MyMath.*;//����MyMath���е����о�̬��Ա

public class Example4_24
{
	public static void main(String args[])
	{
		int a[]={28,37,47,83,42,98,78,23,4,82};
		int x;
		double radius;
		Scanner reader=new Scanner(in);
		
		out.println("����Ԫ�أ�");//System�е�out
		print(a);//MyArray�е�print����
		sort(a);//Arrays�еķ���sort()
		out.println("����Ԫ�������");//System�е�out
		print(a);//MyArray�е�print����
		
		//--------------------------------------
		out.print("����һ��Բ�İ뾶��");
		radius=reader.nextDouble();
		out.printf("�뾶Ϊ%.1f��Բ�����%.2f\n",
				radius,PI*radius*radius);//Math�еľ�̬��PI
		
		//--------------------------------------
		out.print("����һ����Ȼ����");//System�е�out
		x=reader.nextInt();
		
		if(isPrime(x))//MyMath�е�isPrime()����
			out.print(x+"��һ������");//System�е�out
		else
			out.print(x+"����һ������");//System�е�out
	}
}
