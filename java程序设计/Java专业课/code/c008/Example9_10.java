import java.awt.BorderLayout;
import java.awt.FlowLayout;
import javax.swing.*;
class FrameWithBoxLayout extends JFrame
{
	Box box1,box2,box;
	public void display()
	{
		setLayout(new FlowLayout());
		box1=Box.createVerticalBox();//创建一个列排列的Box，存放提示信息
		box2=Box.createVerticalBox();//创建一个列排列的Box，存放输入文本框
		box=Box.createHorizontalBox();//创建一个行排列的Box，存放box1和box2
		
		box1.add(new JLabel("用户名："));//向列排列box1中加入一个label
		box1.add(Box.createVerticalStrut(10));//向box1中加入一个高10像素的间隔组件
		box1.add(new JLabel("密码："));
		box1.add(Box.createVerticalStrut(10));
		box1.add(new JLabel("重复密码："));
		
		box2.add(new JTextField(10));
		box2.add(Box.createVerticalStrut(10));
		box2.add(new JTextField(10));
		box2.add(Box.createVerticalStrut(10));
		box2.add(new JTextField(10));
		box2.add(Box.createVerticalStrut(10));
		
		box.add(box1);
		box.add(Box.createHorizontalStrut(10));//向box中加入一个宽10像素的间隔组件
		box.add(box2);
		add(box,BorderLayout.CENTER);
		
		pack();
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_10
{
	public static void main(String[] args)
	{
		new FrameWithBoxLayout().display();
	}
}
