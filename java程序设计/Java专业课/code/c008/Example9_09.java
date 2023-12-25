import java.awt.*;
import javax.swing.*;
class FrameWithGridBagLayout extends JFrame 
{
	void display()
	{
		setTitle("��������ֹ�����ʾ��");
		JTextField text=new JTextField();
		add(text, BorderLayout.NORTH);   
		
		JPanel p = new JPanel();//����һ��JPanel��������
		GridBagLayout layout = new GridBagLayout();
		p.setLayout(layout);//JPanel�Ĳ���Ϊ���������
		
		String[] name = {"C","�R","*","��","7","8","9","-",
				"4","5","6","+","1","2","3","��","0","."};
		JButton [] button=new JButton[name.length];
		for (int i = 0; i < name.length; ++i)
			button[i]=new JButton(name[i]);
		//����һ��GridBagConstraints��ʹ���������ʾ����
		GridBagConstraints s= new GridBagConstraints();
		s.fill = GridBagConstraints.BOTH;
		
		for(int i=1;i<16;i++) 
		{
			if(i%4!=0) //�������ˮƽ��ռ�õ������������Ϊ0������Ǹ��е����һ��
				s.gridwidth=1; 
			else
				s.gridwidth=0;//�������Ϊ���е����һ�����
			//�������ˮƽ��������ȣ�Ϊ0�����죬��Ϊ0�����Ŵ��������������
			s.weightx = 1; 
			//���������ֱ��������ȣ�Ϊ0�����죬��Ϊ0�����Ŵ��������������
			s.weighty=1; 
			p.add(button[i-1],s);//�����ɵİ�ť����GridBagConstraints����λ�ý������
		}
		s.gridwidth=0;//�������Ϊ���е����һ�����
		s.gridheight=2;//�������ռ��2��
		s.weightx = 1;//���ˮƽ������
		s.weighty=1;//�����ֱ������
		p.add(button[15],s);//����=����ť����Ϊռ������һ��
		
		s.gridx=0;//���λ���ڵ�0��
		s.gridy=4;//���λ���ڵ�4��
		s.gridheight=1;//���ռ��1��
		s.gridwidth=2;//���ռ��2��
		s.weightx = 1;//���ˮƽ������
		s.weighty=1;//�����ֱ������
		//����0����ť�����ڵ�4�У���0����ʾ����ռ������һ�У���������
		p.add(button[16],s); 
		
		s.gridx=2;//���λ���ڵ�2��
		s.gridy=4;//���λ���ڵ�4��
		s.gridwidth=1;//
		s.gridheight=1;
		s.weightx = 0;
		s.weighty=0;
		p.add(button[17],s);//����.����ť�����ڵ�4�У���2����ʾ����������
		
		add(p);//��JPanel�������뵽�����У�Ĭ��Ϊ�м�λ��
		setSize(250,250);//���ô��ڴ�СΪ250*250
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_09
{
	public static void main(String[] args)
	{
		new FrameWithGridBagLayout().display();
	}
}
