import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.Date;

public class Example11_14 {

	public static void main(String[] args) throws Exception{
		RandomAccessFile file = new RandomAccessFile("d:\\data.txt", "rw");//�����ļ�����
		FileChannel channel = file.getChannel();//�����ļ�ͨ��
		ByteBuffer buf = ByteBuffer.allocate(128);//�����ֽڻ�����
		System.out.println("�ļ���С��"+channel.size());//��ʾ�ļ���С
		while(channel.read(buf)!=-1){//��ȡ�ļ����ݲ���ʾ

			buf.flip();//׼����������ȡ
			String str =new String(buf.array()).trim();
			System.out.println(str);
		}
		Date time =new Date();
		String newData = "read file time is:" +time;
		buf.clear();//׼��������д��
		buf.put(newData.getBytes());//�򻺳���д�뵱ǰʱ��
		buf.flip();//׼����������ȡ
		while(buf.hasRemaining()) {
		    channel.write(buf);//��ȡ��������������ͨ��
		}
		channel.close();//�ر�ͨ��
	}
}
