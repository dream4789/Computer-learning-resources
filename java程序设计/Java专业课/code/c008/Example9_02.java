import javax.swing.*;
public class Example9_02
{
	public static void main(String[] args)
	{ //直接生成一个MyFrame类的对象
		new MyFrame("Java应用窗口",200,200,300,200);
	}
}
class MyFrame extends JFrame
{
	MyFrame(String title,int x,int y,int width,int height)
	{
		super(title);//调用父类的构造方法设置窗口标题
		setLocation(x,y);
		setSize(width,height);
		setResizable(false);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);//如果注释掉该行，会有什么变化？
	}
}
