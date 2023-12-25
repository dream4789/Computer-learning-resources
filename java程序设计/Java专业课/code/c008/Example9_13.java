import java.awt.BorderLayout;
import java.awt.event.*;
import javax.swing.*;
class FrameWithMouseEvent extends JFrame
{
	JButton button1,button2;
	JTextField text;
	Listen listen;
	void display()
	{
		button1 = new JButton("按钮1");//创建待监听的按钮组件1
		button2 = new JButton("按钮2");//创建待监听的按钮组件2
		text = new JTextField(10);//创建JTextField组件，用于显示监听信息
		
		listen = new Listen();// 创建一个继承了MouseAdapter类的事件监视器
		listen.setButton(button1, button2, text);//传递待监听对象到事件监视器
		
		button1.addMouseListener(listen);//注册事件监视器
		button2.addMouseListener(listen);
		
		add(button1, BorderLayout.SOUTH);
		add(text, BorderLayout.CENTER);
		add(button2, BorderLayout.NORTH);
		
		setSize(300, 200);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_13
{
	public static void main(String[] args)
	{
		new FrameWithMouseEvent().display();
	}
}
class Listen extends MouseAdapter
{//定义一个监听类，继承MouseAdapter类，实现鼠标动作的监听和处理
	JButton button1;
	JButton button2;
	JTextField text;
	public void setButton(JButton b1,JButton b2,JTextField t)
	{//传递组件对象到类中
		this.button1=b1;
		this.button2=b2;
		this.text=t;
	}
	public void mouseClicked(MouseEvent e)
	{//重写mouseClicked方法，完成鼠标点击事件的处理
		if(e.getSource()==button1)
		{//鼠标点击的是按钮1
			if(e.getButton()==MouseEvent.BUTTON1)//鼠标左键被按下
				text.setText("点击了"+button1.getText()+"的左键 ");
			if(e.getButton()==MouseEvent.BUTTON3)//鼠标右键被按下
				text.setText("点击了"+button1.getText()+"的右键 ");
			text.setText(text.getText()+e.getClickCount()+"次"+";"
				+"点击的坐标位置是："+e.getX()+","+e.getY());
		}
		else if(e.getSource()==button2)
		{//鼠标点击的是按钮2
			if(e.getButton()==MouseEvent.BUTTON1)//鼠标左键被按下
				text.setText("点击了"+button2.getText()+"的左键 ");
			if(e.getButton()==MouseEvent.BUTTON3)//鼠标右键被按下
				text.setText("点击了"+button2.getText()+"的右键 ");
			text.setText(text.getText()+e.getClickCount()+"次"+";"
				+"点击的坐标位置是："+e.getX()+","+e.getY());
		}
	}
}
