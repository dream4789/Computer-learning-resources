import javax.swing.*;
import java.awt.*;
class FrameWithFlowLayout extends JFrame
{
	JButton button1,button2,button3;
	JTextField text1,text2;
	FlowLayout f;
	
	void display()
	{
		f=new FlowLayout();//创建FlowLayout布局
		setLayout(f);//设置当前窗口的布局管理器
		setTitle("流式布局管理器示例");//设置窗口标题栏
		
		button1=new JButton("第一个按钮");//创建按钮对象
		button2=new JButton("第二个按钮");
		button3=new JButton("第三个按钮");
		add(button1);//将按钮加入窗口
		add(button2);
		add(button3);
		
		text1=new JTextField(10);//设置文本框对象
		text1.setText("第一个文本框");//设置文本框的初始内容
		text2=new JTextField(10);
		text2.setText("第二个文本框");
		add(text1);//将文本框加入窗口
		add(text2);
		setSize(300,200);//设置窗口大小
		setVisible(true);//设置窗口为可见
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_06
{
	public static void main(String[] args)
	{
		FrameWithFlowLayout flow = new FrameWithFlowLayout();
		flow.display();
	}
}
