import java.util.Scanner;
import java.io.*;
public class Example11_09
{
	public static void main(String[] args)
	{
		File file;
		FileReader fin;
		FileWriter fout;
		BufferedReader bin;
		BufferedWriter bout;
		Scanner scanner = new Scanner(System.in);
		System.out.println("请输入文件名，例如d:\\hello.txt");
		String filename = scanner.nextLine();
	
		try
		{
			file = new File(filename);//创建文件对象
			if (!file.exists())
			{
				file.createNewFile();//创建新文件
				fout = new FileWriter(file);//创建文件输出流对象
			} 
			else
				fout = new FileWriter(file, true);//创建追加内容的文件输出流对象
	
			fin = new FileReader(file);//创建文件输入流
			bin = new BufferedReader(fin);//创建缓冲输入流
			bout = new BufferedWriter(fout);//创建缓冲输出流
			
			System.out.println("请输入数据，最后一行为字符‘0’结束。");
			String str = scanner.nextLine();//从键盘读取待输入字符串
			while (!str.equals("0"))
			{
				bout.write(str);//输出字符串内容
				bout.newLine();//输出换行符
				str = scanner.nextLine();//读下一行
			}
			bout.flush();//刷新输出流
			bout.close();//关闭缓冲输出流
			fout.close();//关闭文件输出流
			System.out.println("文件写入完毕！");	
			//重新将文件内容显示出来
			System.out.println("文件" + filename + "的内容是：");
			while ((str = bin.readLine()) != null)
				System.out.println(str);//读取文件内容并显示
	
			bin.close();//关闭缓冲输入流
			fin.close();//关闭文件输入流
		}
		catch (IOException e)
		{e.printStackTrace();}
	}
}
