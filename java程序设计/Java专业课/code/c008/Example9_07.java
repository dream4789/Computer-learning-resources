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
		
		add(ebutton,BorderLayout.EAST);//����ť�ӵ����ڵ�ָ��λ��
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
