import javax.swing.*;
import java.awt.*;
class FrameWithBorderLayout extends JFrame
{
	JButton ebutton,wbutton,nbutton,sbutton,cbutton;
	JTextField text;
	
	void display()
	{
		setTitle("�߽粼�ֹ�����ʾ��");
		ebutton=new JButton("��");//������ť����
		wbutton=new JButton("��");
		sbutton=new JButton("��");
		nbutton=new JButton("��");
		cbutton=new JButton("��");
		
		JPanel panel = new JPanel();//����JPanel����
		text=new JTextField("�м�����");
		panel.add(text);//��JPanel�м������
		panel.add(cbutton);
		
		add(ebutimport java.awt.*;
import javax.swing.*;
class FrameWithGridLayout extends JFrame
{
	void display()
	{
		setTitle("���񲼾ֹ�����ʾ��");
		JTextField text=new JTextField(20);
		add(text, BorderLayout.NORTH);
		
		JPanel p = new JPanel();//����һ��JPanel��������       
		//��JPanel�Ĳ��ֹ���������Ϊ���񲼾ֹ�������
		//����Ϊ4��3�У�����֮���С��м���Ϊ4������
		p.setLayout(new GridLayout(4,3,4,4));
		String[] name = {"1","2","3","4","5","6","7","8","9","*","0","#"};
		for (int i = 0; i < name.length; ++i)
			p.add(new JButton(name[i]));//JPanel�ĸ��������м��밴ť����
		add(p);//��JPanel�������뵽�����У�Ĭ��Ϊ�м�λ��
		pack();//���ô���Ϊ���ʴ�С
		
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_08
{
	public static void main(String[] args)
	{
		new FrameWithGridLayout().display();
	}
}
on,BorderLayout.EAST);//����ť�ӵ����ڵ�ָ��λ��
		add(wbutton, BorderLayout.WEST);
		add(sbutton, BorderLayout.SOUTH);
		add(nbutton, BorderLayout.NORTH);
		add(panel, BorderLayout.CENTER);//��JPanel�����ӵ����ڵ�ָ��λ��
		setSize(300,300);//���ô��ڴ�С
		setVisible(true);//���ô��ڿɼ�
		setDefaultCloseOperation(EXIT_ON_CLOSE);	
	}
}
public class Example9_07
{
	public static void main(String[] args)
	{
		FrameWithBorderLayout ex=new FrameWithBorderLayout();
		ex.display();//��ʾ��������
	}
}
