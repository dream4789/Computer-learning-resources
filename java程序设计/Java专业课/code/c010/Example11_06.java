import java.io.*;
import java.util.Scanner;
public class Example11_06
{
	public static void main(String[] args)
	{
		String content;//待输出字符串
		byte[] b;//输出字节流
		FileOutputStream out;//文件输出流
		Scanner scanner = new Scanner(System.in);
		System.out.println("请输入文件名：（例如，d:\\hello.txt）");
		String filename=scanner.nextLine();
		File file = new File(filename);//创建文件对象
	
		if (!file.exists())
		{//判断文件是否存在
			System.out.println("文件不存在，是否创建？(y/n)");
			String f =scanner.nextLine();
			if (f.equalsIgnoreCase("n"))
				System.exit(0);//不创建，退出
			else
			{
				try
				{
					file.createNewFile();//创建新文件
				}
				catch(IOException e)
				{
					System.out.println("创建失败");
					System.exit(0);
				}
			}
		}
		
		try
		{//向文件中写内容
			content="Hello";
			b=content.getBytes();
			out = new FileOutputStream(file);//建立文件输出流
			out.write(b);//完成写操作
			out.close();//关闭输出流
			System.out.println("文件写操作成功！");
		}
		catch(IOException e)
		{e.getMessage();}
		
		try
		{//向文件中追加内容
			System.out.println("请输入追加的内容：");
			content = scanner.nextLine();
			b=content.getBytes();
			out = new FileOutputStream(file,true);//创建可追加内容的输出流
			out.write(b);//完成追加写操作
			out.close();//关闭输出流
			System.out.println("文件追加写操作成功！");
			scanner.close();
		}
		catch(IOException e)
		{e.getMessage();}
	}
}
