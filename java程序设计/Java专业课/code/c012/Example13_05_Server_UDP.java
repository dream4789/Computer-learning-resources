import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
public class Example13_05_Server_UDP
{
	public static void main(String[] args)
	{
		DatagramSocket socket=null;
		DatagramPacket packet_send=null;
		DatagramPacket packet_receive=null;
		int port=8158;//�����������˿�
		try
		{
			socket=new DatagramSocket(port);//�������Ӷ���
			System.out.println("�����������ɹ���");
			byte [] r=new byte[1024];//������������
			packet_receive=new DatagramPacket(r,r.length);//�������ݰ�����
			socket.receive(packet_receive);//�������ݰ�
			InetAddress client_ip=packet_receive.getAddress();//�ͻ�����ַ
			int client_port=packet_receive.getPort();//�ͻ����˿ں�
			byte [] data=packet_receive.getData();//�ͻ����ֽ�����
			int len=packet_receive.getLength();//������Ч����
			String str1=new String (data,0,len);//���ֽ�����ת�����ַ���
			System.out.println("�ͻ���"+client_ip+":"+client_port+"\n���͵���Ϣ�ǣ�"+str1);
			String response="��ã����Ƿ�����";
			byte [] s=response.getBytes();
//������Ӧ���ݰ�����
			packet_send=new DatagramPacket(s,s.length,client_ip,client_port); 
			socket.send(packet_send);//������Ӧ���ݰ�
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
