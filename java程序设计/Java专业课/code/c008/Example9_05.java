import javax.swing.*;
public class Example9_05
{
	public static void main(String[] args)
	{
		JFrame frame = new JFrame("window");
		JWindow window =new JWindow(frame);//创建一个JWindow窗口
		window.setSize(200,200);
		frame.setSize(300,300);
		JButton b = new JButton("按钮");
		window.add(b);//向JWindow窗口中加入按钮
		frame.setVisible(true);
		window.setLocationRelativeTo(frame);//设置JWindow窗口显示位置
		window.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
