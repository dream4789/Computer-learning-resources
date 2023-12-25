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
		
		add(ebutton,BorderLayout.EAST);//将按钮加到窗口的指定位置
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
