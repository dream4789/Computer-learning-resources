import java.io.*;
import java.util.Scanner;

public class Example11_03
{
	public static void main(String[] args)
	{
		Scanner scanner = new Scanner(System.in);
		System.out.println("请输入文件所在的路径：");
		String s = scanner.nextLine();//读取待访问的路径
		
		File dirFile = new File(s);//创建目录文件对象
		String[] allresults = dirFile.list();//获取目录下的所有文件名
		File []files =new File[allresults.length];
		for (int i=0;i<allresults.length;i++){//创建完整文件名对象
			
			 files[i]=new File(dirFile.getAbsolutePath().toString()+"\\"+allresults[i]);
		}
		int i=1;
		String number;
		for (File f:files){
			if(f.exists()){
				if(i<10){//根据要求创建编号字符串，3位数字
					 number="C00"+i+" ";
				}else if(i>=10 & i<99){
					 number="C0"+i+" ";
				}else{
					 number="C"+i+" ";
				}
				String a=f.getParent().toString()+File.separator+number+f.getName();
				File file= new File(a);//创建带有编号的新文件对象
			f.renameTo(file);//修改文件名
			i++;
			}
		}
	}
}
