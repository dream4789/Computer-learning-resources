import java.nio.ByteBuffer;
import java.nio.channels.*;

public class Example11_13 {
	public static void main(String[] args) throws Exception{
		ReadableByteChannel in = Channels.newChannel(System.in);// 创建一个读通道
		WritableByteChannel out = Channels.newChannel(System.out);// 创建一个写通道
		ByteBuffer buff = ByteBuffer.allocate(1024);// 创建一个1024字节的字节缓冲区
		while (in.read(buff) != -1) {// 将读通道的数据读到缓冲区
				buff.flip();// 翻转缓冲区
				String str = new String(buff.array()).trim();
				if (str.equals("exit")) {// 若输入"exit"则结束
					in.close();
					out.close();
					break;
				}
				out.write(buff);// 将缓冲区的数据写入到写通道
				while (buff.hasRemaining()) {// 查询缓冲区是否还有剩余数据
					out.write(buff);
				}
				buff.clear();// 清空缓冲区，准备写入下一批数据
		}
	}
}
