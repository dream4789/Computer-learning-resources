import java.awt.*;
import javax.swing.*;
class FrameWithGridBagLayout extends JFrame 
{
	void display()
	{
		setTitle("网格包布局管理器示例");
		JTextField text=new JTextField();
		add(text, BorderLayout.NORTH);   
		
		JPanel p = new JPanel();//设置一个JPanel容器对象
		GridBagLayout layout = new GridBagLayout();
		p.setLayout(layout);//JPanel的布局为网格包布局
		
		String[] name = {"C","㏑","*","÷","7","8","9","-",
				"4","5","6","+","1","2","3","＝","0","."};
		JButton [] button=new JButton[name.length];
		for (int i = 0; i < name.length; ++i)
			button[i]=new JButton(name[i]);
		//定义一个GridBagConstraints，使组件充满显示区域
		GridBagConstraints s= new GridBagConstraints();
		s.fill = GridBagConstraints.BOTH;
		
		for(int i=1;i<16;i++) 
		{
			if(i%4!=0) //设置组件水平所占用的网格数，如果为0，组件是该行的最后一个
				s.gridwidth=1; 
			else
				s.gridwidth=0;//设置组件为该行的最后一个组件
			//设置组件水平的拉伸幅度，为0不拉伸，不为0就随着窗口增大进行拉伸
			s.weightx = 1; 
			//设置组件垂直的拉伸幅度，为0不拉伸，不为0就随着窗口增大进行拉伸
			s.weighty=1; 
			p.add(button[i-1],s);//将生成的按钮按照GridBagConstraints设置位置进行添加
		}
		s.gridwidth=0;//设置组件为该行的最后一个组件
		s.gridheight=2;//设置组件占用2行
		s.weightx = 1;//组件水平可拉伸
		s.weighty=1;//组件垂直可拉伸
		p.add(button[15],s);//将“=”按钮设置为占用两行一列
		
		s.gridx=0;//组件位置在第0列
		s.gridy=4;//组件位置在第4行
		s.gridheight=1;//组件占用1行
		s.gridwidth=2;//组件占用2列
		s.weightx = 1;//组件水平可拉伸
		s.weighty=1;//组件垂直可拉伸
		//将“0”按钮设置在第4行，第0列显示，并占用两列一行，添加入面板
		p.add(button[16],s); 
		
		s.gridx=2;//组件位置在第2列
		s.gridy=4;//组件位置在第4行
		s.gridwidth=1;//
		s.gridheight=1;
		s.weightx = 0;
		s.weighty=0;
		p.add(button[17],s);//将“.”按钮设置在第4行，第2列显示，添加入面板
		
		add(p);//将JPanel容器加入到窗口中，默认为中间位置
		setSize(250,250);//设置窗口大小为250*250
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
public class Example9_09
{
	public static void main(String[] args)
	{
		new FrameWithGridBagLayout().display();
	}
}
