import java.awt.*;
import javax.swing.*;
class ChessPad extends JPanel
{//���������࣬���������
	ChessPad()
	{  
		setSize(440,440);//�������̴�С
		setLayout(null);//�������̲���Ϊnull���գ�
		setBackground(Color.orange);//�������̱���ɫΪ��ɫ
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);//���ø��෽������֤��������ʾ
		
		for(int i=40;i<=400;i=i+20)//�������̵ĺ���
			g.drawLine(40,i,400,i);//�Ӹ��������Ͻ����굽���½��������ֱ��
		for(int j=40;j<=400;j=j+20)//�������̵�����
			g.drawLine(j,40,j,400);
		
		//�����̵�ָ��λ�û���ʵ��Բ��ע�������Ͻ����겻��Բ������
		g.fillOval(97,97,6,6);
		g.fillOval(337,97,6,6);
		g.fillOval(97,337,6,6);
		g.fillOval(337,337,6,6);
		g.fillOval(217,217,6,6);
	}
}
class FrameWithNullLayout extends JFrame 
{//��������
	public void display()
	{
		setLayout(null);//���ô��ڲ���Ϊnull���գ����ֹ�����
		ChessPad chesspad = new ChessPad();//��������
		add(chesspad);//�����̼��뵽����
		chesspad.setBounds(5,5,440,440);//���������ڴ����е���ʾλ�úʹ�С
		setSize(460, 470);//���ô��ڴ�С
		setVisible(true);//���ô��ڿɼ�
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_11
{
	public static void main(String[] args)
	{
		new FrameWithNullLayout().display();
	}
}
