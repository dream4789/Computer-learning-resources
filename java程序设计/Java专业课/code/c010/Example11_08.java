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
			System.out.println(inData.readBoolean());//读取boolean数据
			System.out.println(inData.readChar());//读取字符数据
			System.out.println(inData.readInt());//读取int数据
			System.out.println(inData.readLong());//读取long数据 
			System.out.println(+inData.readFloat());//读取float数据
			System.out.println(inData.readDouble());//读取double数据
			
			char c = '\0';
			while((c=inData.readChar())!='\0')//读入字符不为空
				System.out.print(c);
		}
		catch(IOException e){}
	}
}
