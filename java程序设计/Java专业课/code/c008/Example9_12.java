import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;
class ComponentWithActionEvent extends JFrame 	implements ActionListener//实现动作监视器接口
{//创建一个窗口界面
	JButton button_up,button_down,button_first,button_last;//声明所需的按钮组件
	JLabel label1,label2,label3;//声明所需的JLabel组件
	JPanel panel;//声明一个JPanel容器，用于图片的载入和显示
	CardLayout card;//声明一个CardLayout布局管理器，用于组件的叠加存放
	
	public ComponentWithActionEvent()
	{
		button_up=new JButton("上一张");
		button_down=new JButton("下一张");
		button_first=new JButton("第一张");
		button_last=new JButton("最后一张");
		
		label1=new JLabel();//创建JLabel，用于装入图片
		label2=new JLabel();
		label3=new JLabel();
		label1.setIcon(new ImageIcon("1.png"));//将图片加入label，实现图片的显示
		label2.setIcon(new ImageIcon("2.png"));
		label3.setIcon(new ImageIcon("3.png"));
		
		panel=new JPanel();//创建一个JPanel容器，用于载入各个JLabel组件
		card=new CardLayout();//将JPanel容器的布局管理器设为CardLayout，
		panel.setLayout(card);//实现图片的逐一显示
		
		panel.add(label1);//将各个JLabel组件加入到JPanel容器
		panel.add(label2);
		panel.add(label3);
		
		card.first(panel);
		add(panel,BorderLayout.CENTER);//将JPanel容器加入到窗口的中间位置
		add(button_up, BorderLayout.WEST);//将各个按钮组件加入到窗口的指定位置
		add(button_down, BorderLayout.EAST);
		add(button_first, BorderLayout.NORTH);
		add(button_last, BorderLayout.SOUTH);
		
		button_up.addActionListener(this);//注册监视器。用当前对象this作监视器,
		button_down.addActionListener(this);//因为当前对象所在的类实现了ActionEvent
		button_first.addActionListener(this);//接口，所以它可以作监视器
		button_last.addActionListener(this);
		
		setTitle("动作事件示例");
		setSize(260,260);
		setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	//actionPerformed是ActionEvent接口中的方法，必须定义
	//当事件发生后，该方法就会被调用，并将事件对象传递给参数e
	public void actionPerformed(ActionEvent e)
	{//一个监视器同时监视4个按钮，所以要判断是哪一个事件源产生的事件
		if(e.getSource()==button_up)//监听up按钮，显示上一张图片
			card.previous(panel);
		else if(e.getSource()==button_down)//监听down按钮，显示上一张图片
			card.next(panel);
		else if(e.getSource()==button_first)//监听first按钮，显示第一张图片
			card.first(panel);
		if(e.getSource()==button_last)//监听last按钮，显示最后一张图片
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
