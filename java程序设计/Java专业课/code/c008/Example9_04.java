import java.awt.FlowLayout;
import javax.swing.*;
public class Example9_04
{
	public static void main(String[] args)
	{
		new JComponent_UI();
	}
}
class JComponent_UI extends JFrame
{
	JTextField text;
	JButton button;
	JCheckBox checkBox1,checkBox2,checkBox3,checkBox4;
	JRadioButton radio1,radio2;
	ButtonGroup group;
	JComboBox comBox; 
	JTextArea area;
	   
	public JComponent_UI()
	{
		init();
		setSize(300,300);//���ô��ڴ�С
		setVisible(true);//���ô��ڿɼ�
		setDefaultCloseOperation(EXIT_ON_CLOSE);//���ùرմ��ڲ���
	}
	void init() 
	{
		setLayout(new FlowLayout());//���ô��ڲ���Ϊ��ʽ����
		add(new JLabel("�û���:"));//�򴰿��м����±�ǩ
		text=new JTextField(10); 
		add(text);//�򴰿��м����ı���
add(new JLabel("��ʼ����:"));
		add(new JPasswordField(10));
		add(new JLabel("�Ա�:"));
		group = new ButtonGroup(); //������ѡ��ť������
		radio1 = new JRadioButton("��"); 
		radio2 = new JRadioButton("Ů");
		group.add(radio1); //����ѡ��ť����������
		group.add(radio2);
		add(radio1);//�򴰿��м��뵥ѡ��ť
		add(radio2);
				
		add(new JLabel("����:"));
		checkBox1 = new JCheckBox("ϲ��ͽ��"); //������ѡ��
		checkBox2 = new JCheckBox("ϲ������");
		checkBox3 = new JCheckBox("ϲ������");  
		checkBox4 = new JCheckBox("ϲ������");
		add(checkBox1);//�򴰿��м��븴ѡ��
		add(checkBox2);
		add(checkBox3);
		add(checkBox4);
		add(new JLabel("��Ŀ�б�:"));
		comBox = new JComboBox();//���������б�
		comBox.addItem("�������"); //���б��м�����Ŀ
		comBox.addItem("���ݷ���");
		comBox.addItem("���ܴ���"); 
		add(comBox);//�򴰿��м��������б�
		
		add(new JLabel("���ҽ���:"));
		area = new JTextArea(6,12);//�����ı���
		add(new JScrollPane(area));//�򴰿��м�������������ı���
		button=new JButton("ע��"); //����ע�ᰴť
		add(button);//�򴰿��м��밴ť
	}
}
