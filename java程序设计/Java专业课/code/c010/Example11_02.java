import java.io.*;
import java.util.Scanner;

public class Example11_02
{
	    public static void main(String[] args)
	    {
		    Scanner scanner = new Scanner(System.in);
		    System.out.println("������һ��·������");
		    String s = scanner.nextLine();//��ȡ�����ʵ�Ŀ¼
		    File dirFile = new File(s);//����Ŀ¼�ļ�����
		    String[] allresults = dirFile.list();//��ȡĿ¼�µ������ļ���
		    for (String name : allresults)
			   System.out.println(name);//��������ļ���
			System.out.println("������Ҫ��ʾ���ļ���չ��,���磺.java");
		     s = scanner.nextLine();
		     Filter_Name fileAccept = new Filter_Name();//�����ļ������˶���
		     fileAccept.setExtendName(s);//���ù�������
		     String result[] = dirFile.list(fileAccept);//��ȡ�����������ļ���
		     for (String name : result)
			    System.out.println(name);//��������������ļ���
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
	    {//��д�ӿ��еķ��������ù�������
		   return name.endsWith(extendName);
	     }
}
