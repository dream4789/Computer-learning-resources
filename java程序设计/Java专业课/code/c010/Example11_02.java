import java.io.*;
import java.util.Scanner;

public class Example11_02
{
	    public static void main(String[] args)
	    {
		    Scanner scanner = new Scanner(System.in);
		    System.out.println("请输入一个路径名：");
		    String s = scanner.nextLine();//读取待访问的目录
		    File dirFile = new File(s);//创建目录文件对象
		    String[] allresults = dirFile.list();//获取目录下的所有文件名
		    for (String name : allresults)
			   System.out.println(name);//输出所有文件名
			System.out.println("请输入要显示的文件扩展名,例如：.java");
		     s = scanner.nextLine();
		     Filter_Name fileAccept = new Filter_Name();//创建文件名过滤对象
		     fileAccept.setExtendName(s);//设置过滤条件
		     String result[] = dirFile.list(fileAccept);//获取满足条件的文件名
		     for (String name : result)
			    System.out.println(name);//输出满足条件的文件名
	          }
}
class Filter_Name implements FilenameFilter
{
	    String extendName;
	    public void setExtendName(String s)
	    {
		   extendName = s;
	    }
	    public boolean accept(File dir, String name)
	    {//重写接口中的方法，设置过滤内容
		   return name.endsWith(extendName);
	     }
}
