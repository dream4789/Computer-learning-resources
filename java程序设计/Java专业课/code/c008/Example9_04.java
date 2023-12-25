import java.awt.FlowLayout;
import javax.swing.*;
public class Example9_04
{
	public static void main(String[] args)
	{
		new JComponent_UI();
	}
}
class JComponent_UI extends JFrame
{
	JTextField text;
	JButton button;
	JCheckBox checkBox1,checkBox2,checkBox3,checkBox4;
	JRadioButton radio1,radio2;
	ButtonGroup group;
	JComboBox comBox; 
	JTextArea area;
	   
	public JComponent_UI()
	{
		init();
		setSize(300,300);//设置窗口大小
		setVisible(true);//设置窗口可见
		setDefaultCloseOperation(EXIT_ON_CLOSE);//设置关闭窗口操作
	}
	void init() 
	{
		setLayout(new FlowLayout());//设置窗口布局为流式布局
		add(new JLabel("用户名:"));//向窗口中加入新标签
		text=new JTextField(10); 
		add(text);//向窗口中加入文本框
add(new JLabel("初始密码:"));
		add(new JPasswordField(10));
		add(new JLabel("性别:"));
		group = new ButtonGroup(); //创建单选按钮作用域
		radio1 = new JRadioButton("男"); 
		radio2 = new JRadioButton("女");
		group.add(radio1); //将单选按钮加入作用域
		group.add(radio2);
		add(radio1);//向窗口中加入单选按钮
		add(radio2);
				
		add(new JLabel("爱好:"));
		checkBox1 = new JCheckBox("喜欢徒步"); //创建复选框
		checkBox2 = new JCheckBox("喜欢旅游");
		checkBox3 = new JCheckBox("喜欢读书");  
		checkBox4 = new JCheckBox("喜欢音乐");
		add(checkBox1);//向窗口中加入复选框
		add(checkBox2);
		add(checkBox3);
		add(checkBox4);
		add(new JLabel("栏目列表:"));
		comBox = new JComboBox();//创建下拉列表
		comBox.addItem("程序设计"); //向列表中加入条目
		comBox.addItem("数据分析");
		comBox.addItem("智能处理"); 
		add(comBox);//向窗口中加入下拉列表
		
		add(new JLabel("自我介绍:"));
		area = new JTextArea(6,12);//创建文本区
		add(new JScrollPane(area));//向窗口中加入带滚动条的文本区
		button=new JButton("注册"); //创建注册按钮
		add(button);//向窗口中加入按钮
	}
}
