import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.Date;

public class Example11_14 {

	public static void main(String[] args) throws Exception{
		RandomAccessFile file = new RandomAccessFile("d:\\data.txt", "rw");//建立文件对象
		FileChannel channel = file.getChannel();//建立文件通道
		ByteBuffer buf = ByteBuffer.allocate(128);//设置字节缓冲区
		System.out.println("文件大小："+channel.size());//显示文件大小
		while(channel.read(buf)!=-1){//读取文件内容并显示

			buf.flip();//准备缓冲区读取
			String str =new String(buf.array()).trim();
			System.out.println(str);
		}
		Date time =new Date();
		String newData = "read file time is:" +time;
		buf.clear();//准备缓冲区写入
		buf.put(newData.getBytes());//向缓冲区写入当前时间
		buf.flip();//准备缓冲区读取
		while(buf.hasRemaining()) {
		    channel.write(buf);//读取缓冲区内容送入通道
		}
		channel.close();//关闭通道
	}
}
