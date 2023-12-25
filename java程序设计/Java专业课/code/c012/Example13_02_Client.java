import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
public class Example13_02_Client
{
	public static void main(String[] args) 
	{
		Socket client_socket=null;
		DataInputStream in=null;
		DataOutputStream out=null;
		String ip="127.0.0.1";//������IP
		int port=8000;//�������˿�
		try
		{
			client_socket=new Socket(ip,port);//���������������
			in=new DataInputStream(client_socket.getInputStream());//����������
			out=new DataOutputStream(client_socket.getOutputStream());//���������
			out.writeUTF("��ã����ǿͻ���");//��������˷�����Ϣ
			System.out.println("�ͻ����������������������Ϣ����ã����ǿͻ���");
			String str=in.readUTF();//�ȴ���ȡ����������Ӧ����Ϣ����������״̬
			System.out.println("�������˵���Ӧ��Ϣ��"+str);
		}
		catch (Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			try//�ر���������
			{
				in.close();
				out.close();
				client_socket.close();
			}
			catch(Exception e){}
		}
	}
}
