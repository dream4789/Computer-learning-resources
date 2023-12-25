import java.io.*;
public class Example11_08
{
	public static void main(String[] args)
	{
		File file=new File("d:\\data.txt");
		try
		{
			FileOutputStream out=new FileOutputStream(file);
			DataOutputStream outData=new DataOutputStream(out);
			outData.writeBoolean(true);
			outData.writeChar('A');
			outData.writeInt(10);
			outData.writeLong(88888888);  
			outData.writeFloat(3.14f);
			outData.writeDouble(3.1415926897);
			outData.writeChars("hello,every one!");
		} 
		catch(IOException e){}
	
		try
		{
			FileInputStream in=new FileInputStream(file);
			DataInputStream inData=new DataInputStream(in);
			System.out.println(inData.readBoolean());//��ȡboolean����
			System.out.println(inData.readChar());//��ȡ�ַ�����
			System.out.println(inData.readInt());//��ȡint����
			System.out.println(inData.readLong());//��ȡlong���� 
			System.out.println(+inData.readFloat());//��ȡfloat����
			System.out.println(inData.readDouble());//��ȡdouble����
			
			char c = '\0';
			while((c=inData.readChar())!='\0')//�����ַ���Ϊ��
				System.out.print(c);
		}
		catch(IOException e){}
	}
}
