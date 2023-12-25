import java.io.*;
import java.util.Scanner;
public class Example11_07
{
public static void main(String[] args) throws IOException
	{
		Scanner scanner=new Scanner(System.in);
		System.out.println("请输入源文件名和目的文件名，中间用空格分隔");
		String s=scanner.next();//读取源文件名
		String d=scanner.next();//读取目的文件名
		File file1=new File(s);//创建源文件对象
		File file2=new File(d);//创建目的文件对象
		 
		if(!file1.exists())
		{
			System.out.println("被复制的文件不存在");
			System.exit(1);
		}
		
		InputStream input=new FileInputStream(file1);//创建源文件流
		OutputStream output=new FileOutputStream(file2);//创建目的文件流
		if((input!=null)&&(output!=null))
		{
			int temp=0;
			while((temp=input.read())!=(-1))//读入一个字符
				output.write(temp);//复制到新文件中
		}
		input.close();//关闭源文件流
		output.close();//关闭目的文件流
		System.out.println("文件复制成功！");
	}
}
