package C008_FileOpEg;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.RandomAccessFile;
import java.util.Date;

/**
 * project_name: Java_Ex
 *
 * package_name: C008_FileOpEg 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-1 ����7:23:40 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: FileOpTest.java  
 *
 * Description:  
 *
 */
public class FileOpTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		test9();
	}
	
	public static void test9(){//read file properties
		File f = new File("a.txt");   
		if (f.exists()) {
			System.out.println(f.getName() + "���������£� �ļ�����Ϊ��" + f.length());
			System.out.println(f.isFile() ? "���ļ�" : "�����ļ�");
			System.out.println(f.isDirectory() ? "��Ŀ¼" : "����Ŀ¼");
			System.out.println(f.canRead() ? "�ɶ�ȡ" : "��");
			System.out.println(f.canWrite() ? "�������ļ�" : "");
			System.out.println("�ļ��е�����޸�����Ϊ��" + new Date(f.lastModified()));
		} else {
			System.out.println(f.getName() + "���������£�");
			System.out.println(f.isFile() ? "���ļ�" : "�����ļ�");
			System.out.println(f.isDirectory() ? "��Ŀ¼" : "����Ŀ¼");
			System.out.println(f.canRead() ? "�ɶ�ȡ" : "��");
			System.out.println(f.canWrite() ? "�������ļ�" : "");
			System.out.println("�ļ�������޸�����Ϊ��" + new Date(f.lastModified()));
		} 
		
	}
	
	public static void test8(){//write random file
		RandomAccessFile inAndOut = null;
		int data[] = { 20, 30, 40, 50, 60 };
		try {
			inAndOut = new RandomAccessFile("a.txt", "rw");
		} catch (Exception e) {
		}
		try {
			for (int i = 0; i < data.length; i++)
				inAndOut.writeInt(data[i]);
			for (long i = data.length - 1; i >= 0; i--) {
				inAndOut.seek(i * 4);
				System.out.printf("\t%d", inAndOut.readInt());
			}
			inAndOut.close();
		} catch (IOException e) {
		}
	}
	
	@SuppressWarnings("resource")
	public static void test7(){//read random file		
		try {
			RandomAccessFile raf = new RandomAccessFile("racf.txt", "rw");
			long position = 0, length = raf.length();
			raf.seek(position); // position r/w
			while (position < length) {
				String str = raf.readLine();
				byte b[] = str.getBytes("iso-8859-1");
				str = new String(b);
				position = raf.getFilePointer();
				System.out.println(str);
			}
		} catch (IOException ioe) {
			System.out.println("�޷����ļ���" + ioe.getMessage());
		}
	}
	
	public static void test5(){//delete all folder in a folder
		File delfile = new File("FolderForDelete");
		File[] files = delfile.listFiles();
		for (int i = 0; i < files.length; i++) {
			if (files[i].isDirectory()) {
				files[i].delete();
			}
		}
	}
	
	public static void test6() {// delete all files in a folder
		File delfilefolder = new File("FolderForDelete");
		try {
			if (!delfilefolder.exists()) {
				delfilefolder.delete();
			}
			delfilefolder.mkdir();
		} catch (Exception e) {
			System.out.println("���Ŀ¼��������");
			e.printStackTrace();
		}
	}
	
	public static void test3(){//delete file
		File deleteFile = new File("deletefile.txt");
		try {
			deleteFile.delete();
		} catch (Exception e) {
			System.out.println("ɾ���ļ���������");
			e.printStackTrace();
		}		
	}
	
	public static void test4(){//delete folder
		File deleteFolder = new File("deletefolder");
		try {
			deleteFolder.delete(); // ɾ�����ļ���
		} catch (Exception e) {
			System.out.println("ɾ���ļ��в�������");
			e.printStackTrace();
		}
	}
	
	public static void test1() {//create folder
		File myFolderPath = new File("MKDIR");
		try {
			if (!myFolderPath.exists()) {
				myFolderPath.mkdir();
			}
		} catch (Exception e) {
			System.out.println("�½�Ŀ¼��������");
			e.printStackTrace();
		}
	}
	
	public static void test2() {//create file
		File createfile = new File("createfile.txt");
		try {
			if (!createfile.exists()) {
				createfile.createNewFile();
			}
			FileWriter fileWriter = new FileWriter(createfile);
			PrintWriter pwWriter = new PrintWriter(fileWriter);
			pwWriter.println("create a file for test...");
			fileWriter.close();
		} catch (Exception e) {
			System.out.println("�½��ļ���������");
			e.printStackTrace();
		}
	}

}


 