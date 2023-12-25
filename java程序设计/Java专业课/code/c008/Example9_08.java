import javax.swing.*;
import java.awt.*;
class FrameWithBorderLayout extends JFrame
{
	JButton ebutton,wbutton,nbutton,sbutton,cbutton;
	JTextField text;
	
	void display()
	{
		setTitle("边界布局管理器示例");
		ebutton=new JButton("东");//创建按钮对象
		wbutton=new JButton("西");
		sbutton=new JButton("南");
		nbutton=new JButton("北");
		cbutton=new JButton("中");
		
		JPanel panel = new JPanel();//创建JPanel容器
		text=new JTextField("中间区域");
		panel.add(text);//向JPanel中加入组件
		panel.add(cbutton);
		
		add(ebutimport java.awt.*;
import javax.swing.*;
class FrameWithGridLayout extends JFrame
{
	void display()
	{
		setTitle("网格布局管理器示例");
		JTextField text=new JTextField(20);
		add(text, BorderLayout.NORTH);
		
		JPanel p = new JPanel();//设置一个JPanel容器对象       
		//将JPanel的布局管理器设置为网格布局管理器，
		//网格为4行3列，网格之间行、列间距均为4个像素
		p.setLayout(new GridLayout(4,3,4,4));
		String[] name = {"1","2","3","4","5","6","7","8","9","*","0","#"};
		for (int i = 0; i < name.length; ++i)
			p.add(new JButton(name[i]));//JPanel的各个网格中加入按钮对象
		add(p);//将JPanel容器加入到窗口中，默认为中间位置
		pack();//设置窗口为合适大小
		
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_08
{
	public static void main(String[] args)
	{
		new FrameWithGridLayout().display();
	}
}
on,BorderLayout.EAST);//将按钮加到窗口的指定位置
		add(wbutton, BorderLayout.WEST);
		add(sbutton, BorderLayout.SOUTH);
		add(nbutton, BorderLayout.NORTH);
		add(panel, BorderLayout.CENTER);//将JPanel容器加到窗口的指定位置
		setSize(300,300);//设置窗口大小
		setVisible(true);//设置窗口可见
		setDefaultCloseOperation(EXIT_ON_CLOSE);	
	}
}
public class Example9_07
{
	public static void main(String[] args)
	{
		FrameWithBorderLayout ex=new FrameWithBorderLayout();
		ex.display();//显示窗口内容
	}
}
