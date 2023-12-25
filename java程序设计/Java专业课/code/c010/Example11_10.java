import java.io.*;
public class Example11_10
{
	public static void main(String[] args)
	{
		try
		{
			RandomAccessFile file = new RandomAccessFile("file", "rw");
			file.writeInt(10);// 占4个字节
			file.writeDouble(3.14159);// 占8个字节
			//下面的方法先写入字符串长度（占2个字节），再写入字符串内容。读取字符串长度可用readShort()方法
			file.writeUTF("UTF字符串");
			file.writeBoolean(true);// 占1个字节
			file.writeShort(100);// 占2个字节
			file.writeLong(12345678);// 占8个字节
			file.writeUTF("又是一个UTF字符串");
			file.writeFloat(3.14f);// 占4个字节
			file.writeChar('a');// 占2个字节
			
			file.seek(0);// 把文件指针位置设置到文件起始处
			System.out.println("——从file文件起始位置开始读数据——");
			System.out.println(file.readInt());
			System.out.println(file.readDouble());
			System.out.println(file.readUTF());
			//将文件指针跳过3个字节，本例中即跳过了一个boolean值和short值
			file.skipBytes(3);
			System.out.println(file.readLong());
			// 跳过文件中“又是一个UTF字符串”所占字节，
			//注意readShort()方法会移动文件指针，所以不用加2。
			file.skipBytes(file.readShort());
			System.out.println(file.readFloat());
			file.close();
		}
		catch (IOException e)
		{
			System.out.println("文件读写错误！");
		}
	}
}
