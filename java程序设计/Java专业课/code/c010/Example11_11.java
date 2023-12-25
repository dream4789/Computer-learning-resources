import java.io.*;
import java.util.Scanner;
public class Example11_11
{
	public static void main(String[] args)
	{
		try
		{	
			File file;
			FileInputStream fin;
			FileOutputStream fout;
			ObjectInputStream oin;
			ObjectOutputStream oout;
			Scanner scanner = new Scanner(System.in);
			
			System.out.println("请输入文件名，例如d:\\foo");
			String filename = scanner.nextLine();		
			file = new File(filename);//创建文件对象
			if (!file.exists())
				file.createNewFile();//创建新文件
			fout= new FileOutputStream(file);//创建文件输出流
			oout = new ObjectOutputStream(fout);//创建对象输出流
			
			Person person=new Person("张三",20);
			oout.writeObject(person);
			oout.close();//关闭对象输出流
			fout.close();//关闭文件输出流
			System.out.println("对象写入完毕！");
			System.out.println("文件" + filename + "的内容是：");
			
			Person object;
			fin = new FileInputStream(file);//创建文件输入流
			oin = new ObjectInputStream(fin);//创建对象输入流
			try
			{
				object=(Person)oin.readObject();
				System.out.println("读取的对象信息：");
				System.out.println("用户名："+object.getName());
				System.out.println("年龄："+object.getAge());
			}
			catch(ClassNotFoundException e)
			{System.err.println("读取对象失败！");}
			oin.close();//关闭对象输入流
			fin.close();//关闭文件输入流
		}
		catch (IOException e)
		{e.printStackTrace();}
	}
}
class Person implements Serializable//对象串行化
{
	private static final long serialVersionUID = 1234567890L;
	String name;
	int age;

	public Person(String name, int age)
	{
		this.name = name;
		this.age = age;
	}

	public String getName()
	{
		return name;
	}

	public void setName(String name)
	{
		this.name = name;
	}
	public int getAge()
	{
		return age;
	}
	public void setAge(int age)
	{
		this.age = age;
	}
}
