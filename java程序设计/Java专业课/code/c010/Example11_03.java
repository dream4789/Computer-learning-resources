import java.io.*;
import java.util.Scanner;

public class Example11_03
{
	public static void main(String[] args)
	{
		Scanner scanner = new Scanner(System.in);
		System.out.println("�������ļ����ڵ�·����");
		String s = scanner.nextLine();//��ȡ�����ʵ�·��
		
		File dirFile = new File(s);//����Ŀ¼�ļ�����
		String[] allresults = dirFile.list();//��ȡĿ¼�µ������ļ���
		File []files =new File[allresults.length];
		for (int i=0;i<allresults.length;i++){//���������ļ�������
			
			 files[i]=new File(dirFile.getAbsolutePath().toString()+"\\"+allresults[i]);
		}
		int i=1;
		String number;
		for (File f:files){
			if(f.exists()){
				if(i<10){//����Ҫ�󴴽�����ַ�����3λ����
					 number="C00"+i+" ";
				}else if(i>=10 & i<99){
					 number="C0"+i+" ";
				}else{
					 number="C"+i+" ";
				}
				String a=f.getParent().toString()+File.separator+number+f.getName();
				File file= new File(a);//�������б�ŵ����ļ�����
			f.renameTo(file);//�޸��ļ���
			i++;
			}
		}
	}
}
