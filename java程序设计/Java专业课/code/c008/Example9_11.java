import java.awt.*;
import javax.swing.*;
class ChessPad extends JPanel
{//创建棋盘类，面板类容器
	ChessPad()
	{  
		setSize(440,440);//设置棋盘大小
		setLayout(null);//设置棋盘布局为null（空）
		setBackground(Color.orange);//设置棋盘背景色为橙色
	}
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);//调用父类方法，保证背景的显示
		
		for(int i=40;i<=400;i=i+20)//绘制棋盘的横线
			g.drawLine(40,i,400,i);//从给定的左上角坐标到右下角坐标绘制直线
		for(int j=40;j<=400;j=j+20)//绘制棋盘的纵线
			g.drawLine(j,40,j,400);
		
		//在棋盘的指定位置绘制实心圆，注意是左上角坐标不是圆心坐标
		g.fillOval(97,97,6,6);
		g.fillOval(337,97,6,6);
		g.fillOval(97,337,6,6);
		g.fillOval(337,337,6,6);
		g.fillOval(217,217,6,6);
	}
}
class FrameWithNullLayout extends JFrame 
{//创建窗口
	public void display()
	{
		setLayout(null);//设置窗口布局为null（空），手工布局
		ChessPad chesspad = new ChessPad();//创建棋盘
		add(chesspad);//将棋盘加入到窗口
		chesspad.setBounds(5,5,440,440);//设置棋盘在窗口中的显示位置和大小
		setSize(460, 470);//设置窗口大小
		setVisible(true);//设置窗口可见
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_11
{
	public static void main(String[] args)
	{
		new FrameWithNullLayout().display();
	}
}
