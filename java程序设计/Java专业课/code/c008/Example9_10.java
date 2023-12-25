import java.awt.BorderLayout;
import java.awt.FlowLayout;
import javax.swing.*;
class FrameWithBoxLayout extends JFrame
{
	Box box1,box2,box;
	public void display()
	{
		setLayout(new FlowLayout());
		box1=Box.createVerticalBox();//����һ�������е�Box�������ʾ��Ϣ
		box2=Box.createVerticalBox();//����һ�������е�Box����������ı���
		box=Box.createHorizontalBox();//����һ�������е�Box�����box1��box2
		
		box1.add(new JLabel("�û�����"));//��������box1�м���һ��label
		box1.add(Box.createVerticalStrut(10));//��box1�м���һ����10���صļ�����
		box1.add(new JLabel("���룺"));
		box1.add(Box.createVerticalStrut(10));
		box1.add(new JLabel("�ظ����룺"));
		
		box2.add(new JTextField(10));
		box2.add(Box.createVerticalStrut(10));
		box2.add(new JTextField(10));
		box2.add(Box.createVerticalStrut(10));
		box2.add(new JTextField(10));
		box2.add(Box.createVerticalStrut(10));
		
		box.add(box1);
		box.add(Box.createHorizontalStrut(10));//��box�м���һ����10���صļ�����
		box.add(box2);
		add(box,BorderLayout.CENTER);
		
		pack();
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_10
{
	public static void main(String[] args)
	{
		new FrameWithBoxLayout().display();
	}
}
