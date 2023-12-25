import java.awt.FlowLayout;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import javax.swing.*;
class FrameWithItemEvent extends JFrame implements ItemListener 
{//定义一个窗口，继承并实现ItemListener接口
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
		
		add(new JLabel("文本框:"));
		text = new JTextField(10);
		add(text);
		add(new JLabel("按钮:"));
		button = new JButton("确定");
		add(button);
		
		add(new JLabel("选择框:"));
		checkBox1 = new JCheckBox("喜欢音乐");
		checkBox2 = new JCheckBox("喜欢旅游");
		checkBox3 = new JCheckBox("喜欢篮球");
		checkBox1.addItemListener(this);//注册事件监视器，监听JcheckBox组件
		checkBox2.addItemListener(this);
		checkBox3.addItemListener(this);
		add(checkBox1);
		add(checkBox2);
		add(checkBox3);
		
		add(new JLabel("单选按钮:"));
		group = new ButtonGroup();
		radio1 = new JRadioButton("男");
		radio2 = new JRadioButton("女");
		group.add(radio1);
		group.add(radio2);
		add(radio1);
		add(radio2);
		
		add(new JLabel("下拉列表:"));
		comBox = new JComboBox();
		comBox.addItem("请选择");
		comBox.addItem("音乐天地");
		comBox.addItem("武术天地");
		comBox.addItem("象棋乐园");
		comBox.addItemListener(this);//注册事件监视器，监听JComboBox组件
		add(comBox);
		
		add(new JLabel("文本区:"));
		area = new JTextArea(6, 12);
		add(new JScrollPane(area));
		
		setSize(300, 300);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public void itemStateChanged(ItemEvent e)
	{//重写itemStateChanged方法，实现监听的处理
		if(e.getItem()==checkBox1)
		{//如果监听到的对象是checkBox1，显示对象内容和选择状态
			String str=checkBox1.getText()+checkBox1.isSelected();
			area.append(str+"\n");
		}
		else if(e.getItemSelectable()==checkBox2)
		{//如果监听到的对象是checkBox2，显示对象内容和选择状态
			String str=checkBox2.getText()+checkBox2.isSelected();
			area.append(str+"\n");
		}
		else if(e.getSource()==checkBox3)
		{//如果监听到的对象是checkBox3，显示对象内容和选择状态
			String str=checkBox3.getText()+checkBox3.isSelected();
			area.append(str+"\n");
		}
		else if(e.getItemSelectable()==comBox)
		{//如果监听到的对象是comBox，显示当前选择的内容
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
