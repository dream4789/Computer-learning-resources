import java.io.*;
import java.util.Scanner;
public class Example11_01
{
	public static void main(String[] args)
	{
		Scanner scanner=new Scanner(System.in);
		System.out.println("请输入文件名，例如：e:\\example.txt");
		String s=scanner.nextLine();
		File file=new File(s);
				System.out.println("文件名："+file.getName());
		System.out.println("文件大小为："+file.length()+"字节");
		System.out.println("文件所在路径为："+file.getAbsolutePath());
				if (file.isHidden())
		{
			System.out.println("该文件是一个隐藏文件");
		}
		else
		{
			System.out.println("该文件不是一个隐藏文件");
		}
		if (!file.exists())
		{
			System.out.println("该文件不存在");
			try
			{
				file.createNewFile();
				System.out.println("新文件创建成功");
			}
			catch(IOException e){}
		}
	}
}
