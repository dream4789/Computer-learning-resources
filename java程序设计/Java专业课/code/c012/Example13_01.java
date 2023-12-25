import java.net.*;
import java.io.*;
import java.util.*;
public class Example13_01//基于URL对象的访问示例
{	
	public static void main(String[] args) 
	{
		Scanner scanner;//创建一个输入对象
		URL url;//创建一个URL对象
		InputStream in;//创建一个输入流
		String addr;//URL地址的字符串表示
		String str;//输入流的字符串表示
		System.out.println("请输入一个URL地址：");
		scanner=new Scanner(System.in);
		addr=scanner.nextLine();//从键盘读取一个URL字符串
		try
		{
			url=new URL(addr);//创建URL对象
			in=url.openStream();//根据URL对象建立输入流
			byte [] b=new byte[1024];
			int n=-1;
			while ((n=in.read(b))!=-1)//将读取的流内容输出
			{
				str=new String(b,0,n,"UTF-8");
				System.out.print(str);
			}
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
}
