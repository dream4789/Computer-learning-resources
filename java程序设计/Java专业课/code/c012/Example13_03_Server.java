import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
public class Example13_03_Server
{
	public static void main(String[] args)
	{
		ServerSocket server_socket=null;
		Socket socket=null;
		DataInputStream in=null;
		DataOutputStream out=null;
		int port=8000;
		
		try
		{
			server_socket=new ServerSocket(port);//�����󶨶˿ڵķ�������socket
		}
		catch(IOException e)
		{
			System.out.println(e);
		}
		
		try
		{
			System.out.println("������������");
			//���������ܵ����׽��ֵ����ӡ��˷��������Ӵ���֮ǰ��������״̬
socket=server_socket.accept();
			in=new DataInputStream(socket.getInputStream());//����������
			out=new DataOutputStream(socket.getOutputStream());//���������
			String str=in.readUTF();//����������ȡ�ַ�������ȡ����֮ǰ��������״̬
			System.out.println("�ͻ������͹�������Ϣ�ǣ� "+str);
			out.writeUTF("��ã����Ƿ�����");//�������д���ַ���
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
		finally
		{
			try//�ر���������
			{
				out.close();
				in.close();
				socket.close();
				server_socket.close();
			}
			catch(Exception e){}
		}
	}
}
