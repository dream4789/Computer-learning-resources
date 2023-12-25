import javax.swing.JFrame;
public class Example9_01
{
	public static void main(String[] args)
	{
		JFrame frame = new JFrame("Java应用窗口");
		frame.setSize(300, 200);//设置窗口大小为300*200
		//设置窗口左上角坐标为横坐标200像素，纵坐标为200像素
		frame.setLocation(200, 200);
		frame.setResizable(false);//设置窗口是否可以调整大小
		frame.setVisible(true);//设置窗口可见，默认为不可见
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //点击窗口右上角的关闭按钮时关闭程序
	}
}
