import java.nio.ByteBuffer;
import java.nio.channels.*;

public class Example11_13 {
	public static void main(String[] args) throws Exception{
		ReadableByteChannel in = Channels.newChannel(System.in);// ����һ����ͨ��
		WritableByteChannel out = Channels.newChannel(System.out);// ����һ��дͨ��
		ByteBuffer buff = ByteBuffer.allocate(1024);// ����һ��1024�ֽڵ��ֽڻ�����
		while (in.read(buff) != -1) {// ����ͨ�������ݶ���������
				buff.flip();// ��ת������
				String str = new String(buff.array()).trim();
				if (str.equals("exit")) {// ������"exit"�����
					in.close();
					out.close();
					break;
				}
				out.write(buff);// ��������������д�뵽дͨ��
				while (buff.hasRemaining()) {// ��ѯ�������Ƿ���ʣ������
					out.write(buff);
				}
				buff.clear();// ��ջ�������׼��д����һ������
		}
	}
}
