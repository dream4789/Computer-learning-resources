import java.io.*;
public class Example11_10
{
	public static void main(String[] args)
	{
		try
		{
			RandomAccessFile file = new RandomAccessFile("file", "rw");
			file.writeInt(10);// ռ4���ֽ�
			file.writeDouble(3.14159);// ռ8���ֽ�
			//����ķ�����д���ַ������ȣ�ռ2���ֽڣ�����д���ַ������ݡ���ȡ�ַ������ȿ���readShort()����
			file.writeUTF("UTF�ַ���");
			file.writeBoolean(true);// ռ1���ֽ�
			file.writeShort(100);// ռ2���ֽ�
			file.writeLong(12345678);// ռ8���ֽ�
			file.writeUTF("����һ��UTF�ַ���");
			file.writeFloat(3.14f);// ռ4���ֽ�
			file.writeChar('a');// ռ2���ֽ�
			
			file.seek(0);// ���ļ�ָ��λ�����õ��ļ���ʼ��
			System.out.println("������file�ļ���ʼλ�ÿ�ʼ�����ݡ���");
			System.out.println(file.readInt());
			System.out.println(file.readDouble());
			System.out.println(file.readUTF());
			//���ļ�ָ������3���ֽڣ������м�������һ��booleanֵ��shortֵ
			file.skipBytes(3);
			System.out.println(file.readLong());
			// �����ļ��С�����һ��UTF�ַ�������ռ�ֽڣ�
			//ע��readShort()�������ƶ��ļ�ָ�룬���Բ��ü�2��
			file.skipBytes(file.readShort());
			System.out.println(file.readFloat());
			file.close();
		}
		catch (IOException e)
		{
			System.out.println("�ļ���д����");
		}
	}
}
