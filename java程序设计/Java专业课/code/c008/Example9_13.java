import java.awt.BorderLayout;
import java.awt.event.*;
import javax.swing.*;
class FrameWithMouseEvent extends JFrame
{
	JButton button1,button2;
	JTextField text;
	Listen listen;
	void display()
	{
		button1 = new JButton("��ť1");//�����������İ�ť���1
		button2 = new JButton("��ť2");//�����������İ�ť���2
		text = new JTextField(10);//����JTextField�����������ʾ������Ϣ
		
		listen = new Listen();// ����һ���̳���MouseAdapter����¼�������
		listen.setButton(button1, button2, text);//���ݴ����������¼�������
		
		button1.addMouseListener(listen);//ע���¼�������
		button2.addMouseListener(listen);
		
		add(button1, BorderLayout.SOUTH);
		add(text, BorderLayout.CENTER);
		add(button2, BorderLayout.NORTH);
		
		setSize(300, 200);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_13
{
	public static void main(String[] args)
	{
		new FrameWithMouseEvent().display();
	}
}
class Listen extends MouseAdapter
{//����һ�������࣬�̳�MouseAdapter�࣬ʵ����궯���ļ����ʹ���
	JButton button1;
	JButton button2;
	JTextField text;
	public void setButton(JButton b1,JButton b2,JTextField t)
	{//���������������
		this.button1=b1;
		this.button2=b2;
		this.text=t;
	}
	public void mouseClicked(MouseEvent e)
	{//��дmouseClicked���������������¼��Ĵ���
		if(e.getSource()==button1)
		{//��������ǰ�ť1
			if(e.getButton()==MouseEvent.BUTTON1)//������������
				text.setText("�����"+button1.getText()+"����� ");
			if(e.getButton()==MouseEvent.BUTTON3)//����Ҽ�������
				text.setText("�����"+button1.getText()+"���Ҽ� ");
			text.setText(text.getText()+e.getClickCount()+"��"+";"
				+"���������λ���ǣ�"+e.getX()+","+e.getY());
		}
		else if(e.getSource()==button2)
		{//��������ǰ�ť2
			if(e.getButton()==MouseEvent.BUTTON1)//������������
				text.setText("�����"+button2.getText()+"����� ");
			if(e.getButton()==MouseEvent.BUTTON3)//����Ҽ�������
				text.setText("�����"+button2.getText()+"���Ҽ� ");
			text.setText(text.getText()+e.getClickCount()+"��"+";"
				+"���������λ���ǣ�"+e.getX()+","+e.getY());
		}
	}
}
