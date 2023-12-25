import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
public class Example13_04_LogicThread extends Thread
{
	Socket socket=null;
	DataInputStream in=null;
	DataOutputStream out=null;
	String str;
	String response;
	String ip;
	int port;
	
	public Example13_04_LogicThread(Socket socket)
	{
		this.socket=socket;
		start();
	}
	public void run()
	{
		try
		{
			in=new DataInputStream(socket.getInputStream());//����������
			out=new DataOutputStream(socket.getOutputStream());//���������
			ip=socket.getInetAddress().getHostAddress();//��ȡ�ͻ���IP��ַ
			port=socket.getPort();//��ȡ�ͻ��˵Ķ˿ں�
			
			while (true)
			{
				str=in.readUTF();//��ȡ�ͻ��˵ı��ʽ
				System.out.println("�ͻ���"+ip+":"+port+"���͵��������ݣ�");
				System.out.println(str+"=?");
				
				if (str.equals("0"))
				{
					System.out.println("���ӽ���");
					break;
				}
				else
				{
					response =doComputer(str);//�Ա��ʽ���м���
					out.writeUTF(response);//��Ӧ������
				}
			}
		}
		catch(Exception e)
		{
			System.out.println("���ӽ���");
		}
		finally
		{
			try
			{
				in.close();
				out.close();
				socket.close();
			}
			catch(Exception e){}
		}
	}
	public String doComputer(String str)
	{
		String input;
		String[] sym;
		String [] data;
		int a=0,b=0,result=0;
		input = str;
		data = input.split("\\D+");//�ֽ���ʽ�е�������
		sym = input.split("\\d+");//�ֽ���ʽ�е������
		a = Integer.parseInt(data[0]);//��һ��������
		b = Integer.parseInt(data[1]);//�ڶ���������
		
		try
		{
			switch(sym[1])//�ж�������������Ӧ������
			{
			case "+":
				result=a+b;break;
			case "-":
				result=a-b;break;
			case "*":
				result=a*b;break;
			case "/":
				result=a/b;
			}
			System.out.println("��������"+input+"="+result);
			return String.valueOf(result);
		}
		catch(java.lang.ArithmeticException e)
		{
			System.out.println("���ݴ���!");
			return "���ݴ���!";
		}
	}
}
