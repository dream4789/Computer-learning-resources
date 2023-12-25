在包classeslib中分别创建两个程序文件MyMath.java和MyArray.java。
程序MyMath.java：
package classeslib;

import static java.lang.Math.sqrt;//只引入Math类中的静态方法sqrt

public class MyMath
{
	public static boolean isPrime(int x)//静态方法，判断一个数是素数？
	{
		if(x<=1)
			return false;
		
		int y=(int)sqrt(x);//Math中的sqrt
		
		for(int i=2;i<=y;i++)
			if(x%i==0)
				return false;
		
		return true;		
	}
}
程序MyArray.java：
package classeslib;

import static java.lang.System.out;//只引入System.类中的静态域out

public class MyArray
{
	public static void print(int a[])//静态方法，打印一个整型数组
	{
		for(int x:a)
			out.print(" "+x);//System中的out
		out.println();//System中的out
	}
}
再在包classeslib的上一级包中创建程序文件Example4_24.java：
import static java.lang.System.*;//引入System中的所有静态成员
import static java.lang.Math.PI;//只引入Math类中的静态域PI
import static java.util.Arrays.sort;//只引入Arrays类中的静态方法sort

import java.util.Scanner;

//引入自定义包中类
import static classeslib.MyArray.*;//引入MyArray类中的所有静态成员
import static classeslib.MyMath.*;//引入MyMath类中的所有静态成员

public class Example4_24
{
	public static void main(String args[])
	{
		int a[]={28,37,47,83,42,98,78,23,4,82};
		int x;
		double radius;
		Scanner reader=new Scanner(in);
		
		out.println("数组元素：");//System中的out
		print(a);//MyArray中的print方法
		sort(a);//Arrays中的方法sort()
		out.println("数组元素排序后：");//System中的out
		print(a);//MyArray中的print方法
		
		//--------------------------------------
		out.print("输入一个圆的半径：");
		radius=reader.nextDouble();
		out.printf("半径为%.1f的圆的面积%.2f\n",
				radius,PI*radius*radius);//Math中的静态域PI
		
		//--------------------------------------
		out.print("输入一个自然数：");//System中的out
		x=reader.nextInt();
		
		if(isPrime(x))//MyMath中的isPrime()方法
			out.print(x+"是一个素数");//System中的out
		else
			out.print(x+"不是一个素数");//System中的out
	}
}
