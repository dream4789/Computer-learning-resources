import javax.swing.*;
public class Example9_05
{
	public static void main(String[] args)
	{
		JFrame frame = new JFrame("window");
		JWindow window =new JWindow(frame);//����һ��JWindow����
		window.setSize(200,200);
		frame.setSize(300,300);
		JButton b = new JButton("��ť");
		window.add(b);//��JWindow�����м��밴ť
		frame.setVisible(true);
		window.setLocationRelativeTo(frame);//����JWindow������ʾλ��
		window.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
