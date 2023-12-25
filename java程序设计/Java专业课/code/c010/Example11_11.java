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
			
			System.out.println("�������ļ���������d:\\foo");
			String filename = scanner.nextLine();		
			file = new File(filename);//�����ļ�����
			if (!file.exists())
				file.createNewFile();//�������ļ�
			fout= new FileOutputStream(file);//�����ļ������
			oout = new ObjectOutputStream(fout);//�������������
			
			Person person=new Person("����",20);
			oout.writeObject(person);
			oout.close();//�رն��������
			fout.close();//�ر��ļ������
			System.out.println("����д����ϣ�");
			System.out.println("�ļ�" + filename + "�������ǣ�");
			
			Person object;
			fin = new FileInputStream(file);//�����ļ�������
			oin = new ObjectInputStream(fin);//��������������
			try
			{
				object=(Person)oin.readObject();
				System.out.println("��ȡ�Ķ�����Ϣ��");
				System.out.println("�û�����"+object.getName());
				System.out.println("���䣺"+object.getAge());
			}
			catch(ClassNotFoundException e)
			{System.err.println("��ȡ����ʧ�ܣ�");}
			oin.close();//�رն���������
			fin.close();//�ر��ļ�������
		}
		catch (IOException e)
		{e.printStackTrace();}
	}
}
class Person implements Serializable//�����л�
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
