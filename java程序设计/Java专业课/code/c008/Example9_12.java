import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;
class ComponentWithActionEvent extends JFrame 	implements ActionListener//ʵ�ֶ����������ӿ�
{//����һ�����ڽ���
	JButton button_up,button_down,button_first,button_last;//��������İ�ť���
	JLabel label1,label2,label3;//���������JLabel���
	JPanel panel;//����һ��JPanel����������ͼƬ���������ʾ
	CardLayout card;//����һ��CardLayout���ֹ���������������ĵ��Ӵ��
	
	public ComponentWithActionEvent()
	{
		button_up=new JButton("��һ��");
		button_down=new JButton("��һ��");
		button_first=new JButton("��һ��");
		button_last=new JButton("���һ��");
		
		label1=new JLabel();//����JLabel������װ��ͼƬ
		label2=new JLabel();
		label3=new JLabel();
		label1.setIcon(new ImageIcon("1.png"));//��ͼƬ����label��ʵ��ͼƬ����ʾ
		label2.setIcon(new ImageIcon("2.png"));
		label3.setIcon(new ImageIcon("3.png"));
		
		panel=new JPanel();//����һ��JPanel�����������������JLabel���
		card=new CardLayout();//��JPanel�����Ĳ��ֹ�������ΪCardLayout��
		panel.setLayout(card);//ʵ��ͼƬ����һ��ʾ
		
		panel.add(label1);//������JLabel������뵽JPanel����
		panel.add(label2);
		panel.add(label3);
		
		card.first(panel);
		add(panel,BorderLayout.CENTER);//��JPanel�������뵽���ڵ��м�λ��
		add(button_up, BorderLayout.WEST);//��������ť������뵽���ڵ�ָ��λ��
		add(button_down, BorderLayout.EAST);
		add(button_first, BorderLayout.NORTH);
		add(button_last, BorderLayout.SOUTH);
		
		button_up.addActionListener(this);//ע����������õ�ǰ����this��������,
		button_down.addActionListener(this);//��Ϊ��ǰ�������ڵ���ʵ����ActionEvent
		button_first.addActionListener(this);//�ӿڣ�������������������
		button_last.addActionListener(this);
		
		setTitle("�����¼�ʾ��");
		setSize(260,260);
		setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	//actionPerformed��ActionEvent�ӿ��еķ��������붨��
	//���¼������󣬸÷����ͻᱻ���ã������¼����󴫵ݸ�����e
	public void actionPerformed(ActionEvent e)
	{//һ��������ͬʱ����4����ť������Ҫ�ж�����һ���¼�Դ�������¼�
		if(e.getSource()==button_up)//����up��ť����ʾ��һ��ͼƬ
			card.previous(panel);
		else if(e.getSource()==button_down)//����down��ť����ʾ��һ��ͼƬ
			card.next(panel);
		else if(e.getSource()==button_first)//����first��ť����ʾ��һ��ͼƬ
			card.first(panel);
		if(e.getSource()==button_last)//����last��ť����ʾ���һ��ͼƬ
			card.last(panel);
	}
}
public class Example9_12
{
	public static void main(String[] args)
	{
		new ComponentWithActionEvent();
	}
}
