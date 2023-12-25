import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
public class Example13_05_Client_UDP
{
	public static void main(String[] args)
	{
		DatagramSocket socket=null;
		DatagramPacket packet_send=null;
		DatagramPacket packet_receive=null;
		String server="127.0.0.1";//��������IP��ַ
		int port=8181;//�������˿ں�
		String str="��ã����ǿͻ���A";
		byte[] data=str.getBytes();//��������Ϣת�����ֽ�����
		
		try
		{
			socket=new DatagramSocket();//��������socket����
//����������IP��ַ��װ��InetAddress����
			InetAddress addr=InetAddress.getByName(server); 
			packet_send=new DatagramPacket(data,data.length,addr,port);//�������ݰ�����
			socket.send(packet_send);//��������˷�������
			byte [] r=new byte[1024];//���ý��ջ�����
			packet_receive=new DatagramPacket(r,r.length);//�������ݰ�����
			socket.receive(packet_receive);//�������ݰ�
			byte [] response=packet_receive.getData();//��ȡ���ݰ��е�������Ϣ
			int len=packet_receive.getLength();//��ȡ���ݳ���
			String str1=new String (response,0,len);//���ֽ�����ת�����ַ���
			System.out.println("��������Ӧ����Ϣ�ǣ�"+str1);
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			socket.close();
		}
	}
}
