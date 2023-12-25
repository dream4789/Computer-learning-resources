import javax.swing.*;
class FrameWithMenu extends JFrame 
{
	JMenuBar menubar;
	JMenu menu1, menu2, menu3, menu4, submenu11, submenu12;
	JMenuItem menuItemOpen, menuItemFlush, menuItemPackage, menuItemClass,
		menuItemClose, menuItemSave, menuItemCut, menuItemPaste,
		menuItemAbout;
	
	void init(String s) 
	{
		setTitle(s);//设置窗口标题
		menubar = new JMenuBar();//创建一个菜单条
		
		menu1 = new JMenu("文件");//创建一个“文件”菜单
		menu2 = new JMenu("编辑");//创建一个“编辑”菜单
		menu3 = new JMenu("搜索");//创建一个“搜索”菜单
		menu4 = new JMenu("帮助");//创建一个“帮助”菜单
		
		submenu11 = new JMenu("新建");//创建一个“新建”子菜单
		//下面是创建菜单项
		menuItemPackage = new JMenuItem("包");//创建一个“包”菜单项
		menuItemClass = new JMenuItem("类");//创建一个“类”菜单项
		menuItemOpen = new JMenuItem("打开");//创建一个“打开”菜单项
		menuItemFlush = new JMenuItem("刷新");//创建一个“刷新”菜单项
		menuItemClose = new JMenuItem("关闭");//创建一个“关闭”菜单项
		menuItemSave = new JMenuItem("保存");//创建一个“保存”菜单项
		menuItemCut = new JMenuItem("剪切");//创建一个“剪切”菜单项
		menuItemPaste = new JMenuItem("粘贴");//创建一个“粘贴”菜单项
		menuItemAbout = new JMenuItem("关于");//创建一个“关于”菜单项
		//下面是将菜单项加入到相应的菜单中
		submenu11.add(menuItemPackage);//将“包”菜单项加入“新建”子菜单
		submenu11.add(menuItemClass);//将“类”菜单项加入“新建”子菜单
		menu1.add(submenu11);//将“新建”子菜单加入“文件”菜单
		menu1.add(menuItemOpen);//将“打开”菜单项加入“文件”菜单
		menu1.add(menuItemClose); //将“关闭”菜单项加入“文件”菜单
		menu1.add(menuItemFlush); //将“刷新”菜单项加入“文件”菜单
		menu1.add(menuItemSave); //将“保存”菜单项加入“文件”菜单
		menu2.add(menuItemCut); //将“剪切”菜单项加入“编辑”菜单
		menu2.add(menuItemPaste); //将“粘贴”菜单项加入“编辑”菜单
		menu4.add(menuItemAbout); //将“关于”菜单项加入“帮助”菜单
		//下面是将菜单加入到菜单条中
		menubar.add(menu1);//将“文件”菜单加入菜单条
		menubar.add(menu2);//将“编辑”菜单加入菜单条
		menubar.add(menu3);//将“搜索”菜单加入菜单条
		menubar.add(menu4);//将“帮助”菜单加入菜单条
		
		setJMenuBar(menubar);//设置窗口菜单条
		setLocation(100, 300);//窗口位置
		setSize(300, 200);//窗口大小
		setVisible(true);//窗口可见
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}

public class Example9_03
{
	public static void main(String[] args)
	{//创建对象后初始化
		new FrameWithMenu().init("Java 菜单设计");
	}
}
