import java.awt.FlowLayout;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import javax.swing.*;
class FrameWithItemEvent extends JFrame implements ItemListener 
{//����һ�����ڣ��̳в�ʵ��ItemListener�ӿ�
	JTextField text;
	JButton button;
	JCheckBox checkBox1,checkBox2,checkBox3;
	JRadioButton radio1, radio2;
	ButtonGroup group;
	JComboBox comBox;
	JTextArea area;
	
	public void display()
	{
		setLayout(new FlowLayout());
		
		add(new JLabel("�ı���:"));
		text = new JTextField(10);
		add(text);
		add(new JLabel("��ť:"));
		button = new JButton("ȷ��");
		add(button);
		
		add(new JLabel("ѡ���:"));
		checkBox1 = new JCheckBox("ϲ������");
		checkBox2 = new JCheckBox("ϲ������");
		checkBox3 = new JCheckBox("ϲ������");
		checkBox1.addItemListener(this);//ע���¼�������������JcheckBox���
		checkBox2.addItemListener(this);
		checkBox3.addItemListener(this);
		add(checkBox1);
		add(checkBox2);
		add(checkBox3);
		
		add(new JLabel("��ѡ��ť:"));
		group = new ButtonGroup();
		radio1 = new JRadioButton("��");
		radio2 = new JRadioButton("Ů");
		group.add(radio1);
		group.add(radio2);
		add(radio1);
		add(radio2);
		
		add(new JLabel("�����б�:"));
		comBox = new JComboBox();
		comBox.addItem("��ѡ��");
		comBox.addItem("�������");
		comBox.addItem("�������");
		comBox.addItem("������԰");
		comBox.addItemListener(this);//ע���¼�������������JComboBox���
		add(comBox);
		
		add(new JLabel("�ı���:"));
		area = new JTextArea(6, 12);
		add(new JScrollPane(area));
		
		setSize(300, 300);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public void itemStateChanged(ItemEvent e)
	{//��дitemStateChanged������ʵ�ּ����Ĵ���
		if(e.getItem()==checkBox1)
		{//����������Ķ�����checkBox1����ʾ�������ݺ�ѡ��״̬
			String str=checkBox1.getText()+checkBox1.isSelected();
			area.append(str+"\n");
		}
		else if(e.getItemSelectable()==checkBox2)
		{//����������Ķ�����checkBox2����ʾ�������ݺ�ѡ��״̬
			String str=checkBox2.getText()+checkBox2.isSelected();
			area.append(str+"\n");
		}
		else if(e.getSource()==checkBox3)
		{//����������Ķ�����checkBox3����ʾ�������ݺ�ѡ��״̬
			String str=checkBox3.getText()+checkBox3.isSelected();
			area.append(str+"\n");
		}
		else if(e.getItemSelectable()==comBox)
		{//����������Ķ�����comBox����ʾ��ǰѡ�������
			if(e.getStateChange()==ItemEvent.SELECTED)
			{
				String str=comBox.getSelectedItem().toString();
				area.append(str+"\n");
			}
		}
	}
}

public class Example9_14
{
	public static void main(String[] args) 
	{
		new FrameWithItemEvent().display();
	}
}
