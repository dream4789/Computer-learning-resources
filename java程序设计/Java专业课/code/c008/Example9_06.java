import javax.swing.*;
import java.awt.*;
class FrameWithFlowLayout extends JFrame
{
	JButton button1,button2,button3;
	JTextField text1,text2;
	FlowLayout f;
	
	void display()
	{
		f=new FlowLayout();//����FlowLayout����
		setLayout(f);//���õ�ǰ���ڵĲ��ֹ�����
		setTitle("��ʽ���ֹ�����ʾ��");//���ô��ڱ�����
		
		button1=new JButton("��һ����ť");//������ť����
		button2=new JButton("�ڶ�����ť");
		button3=new JButton("��������ť");
		add(button1);//����ť���봰��
		add(button2);
		add(button3);
		
		text1=new JTextField(10);//�����ı������
		text1.setText("��һ���ı���");//�����ı���ĳ�ʼ����
		text2=new JTextField(10);
		text2.setText("�ڶ����ı���");
		add(text1);//���ı�����봰��
		add(text2);
		setSize(300,200);//���ô��ڴ�С
		setVisible(true);//���ô���Ϊ�ɼ�
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_06
{
	public static void main(String[] args)
	{
		FrameWithFlowLayout flow = new FrameWithFlowLayout();
		flow.display();
	}
}
