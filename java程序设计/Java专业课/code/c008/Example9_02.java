import javax.swing.*;
public class Example9_02
{
	public static void main(String[] args)
	{ //ֱ������һ��MyFrame��Ķ���
		new MyFrame("JavaӦ�ô���",200,200,300,200);
	}
}
class MyFrame extends JFrame
{
	MyFrame(String title,int x,int y,int width,int height)
	{
		super(title);//���ø���Ĺ��췽�����ô��ڱ���
		setLocation(x,y);
		setSize(width,height);
		setResizable(false);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);//���ע�͵����У�����ʲô�仯��
	}
}
