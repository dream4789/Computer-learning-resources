import javax.swing.JFrame;
public class Example9_01
{
	public static void main(String[] args)
	{
		JFrame frame = new JFrame("JavaӦ�ô���");
		frame.setSize(300, 200);//���ô��ڴ�СΪ300*200
		//���ô������Ͻ�����Ϊ������200���أ�������Ϊ200����
		frame.setLocation(200, 200);
		frame.setResizable(false);//���ô����Ƿ���Ե�����С
		frame.setVisible(true);//���ô��ڿɼ���Ĭ��Ϊ���ɼ�
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //����������ϽǵĹرհ�ťʱ�رճ���
	}
}
