import java.nio.ByteBuffer;
import java.nio.CharBuffer;

public class Example11_12 {

	public static void main(String[] args) {
		ByteBuffer buffer1 = ByteBuffer.allocate(40);
		ByteBuffer buffer2 = ByteBuffer.allocate(40);
		String str1 = "Java NIO reader";
		byte [] b1 =str1.getBytes();
		char[] str2 = "Java NIO writer".toCharArray();
		CharBuffer cbuffer = buffer2.asCharBuffer();
		for (byte b:b1){
			buffer1.put(b);
		}
		for (char c:str2){
			cbuffer.put(c);
		}
	}
}
