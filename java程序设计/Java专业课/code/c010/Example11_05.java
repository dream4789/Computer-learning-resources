import java.io.*;
import java.util.Scanner;
public class Example11_05
{
	public static void main(String[] args)
	{
		byte[] b=new byte[1024];//设置字节缓冲区
		int n=-1;
		System.out.println("请输入要读取的文件名:(例如：d:\\hello.txt)");
		Scanner scanner =new Scanner(System.in);
		String str=scanner.nextLine();//获取要读取的文件名
		
		try
		{
			FileInputStream in=new FileInputStream(str);//创建字节输入流
			while((n=in.read(b,0,1024))!=-1)
			{//读取文件内容到缓冲区，并显示
				String s=new String (b,0,n);
				System.out.println(s);
			}
			in.close();//读取文件结束，关闭文件
			}
		catch(IOException e)
		{
			System.out.println("文件读取失败");
		}
	}
}
