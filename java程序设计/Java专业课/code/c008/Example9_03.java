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
		setTitle(s);//���ô��ڱ���
		menubar = new JMenuBar();//����һ���˵���
		
		menu1 = new JMenu("�ļ�");//����һ�����ļ����˵�
		menu2 = new JMenu("�༭");//����һ�����༭���˵�
		menu3 = new JMenu("����");//����һ�����������˵�
		menu4 = new JMenu("����");//����һ�����������˵�
		
		submenu11 = new JMenu("�½�");//����һ�����½����Ӳ˵�
		//�����Ǵ����˵���
		menuItemPackage = new JMenuItem("��");//����һ���������˵���
		menuItemClass = new JMenuItem("��");//����һ�����ࡱ�˵���
		menuItemOpen = new JMenuItem("��");//����һ�����򿪡��˵���
		menuItemFlush = new JMenuItem("ˢ��");//����һ����ˢ�¡��˵���
		menuItemClose = new JMenuItem("�ر�");//����һ�����رա��˵���
		menuItemSave = new JMenuItem("����");//����һ�������桱�˵���
		menuItemCut = new JMenuItem("����");//����һ�������С��˵���
		menuItemPaste = new JMenuItem("ճ��");//����һ����ճ�����˵���
		menuItemAbout = new JMenuItem("����");//����һ�������ڡ��˵���
		//�����ǽ��˵�����뵽��Ӧ�Ĳ˵���
		submenu11.add(menuItemPackage);//���������˵�����롰�½����Ӳ˵�
		submenu11.add(menuItemClass);//�����ࡱ�˵�����롰�½����Ӳ˵�
		menu1.add(submenu11);//�����½����Ӳ˵����롰�ļ����˵�
		menu1.add(menuItemOpen);//�����򿪡��˵�����롰�ļ����˵�
		menu1.add(menuItemClose); //�����رա��˵�����롰�ļ����˵�
		menu1.add(menuItemFlush); //����ˢ�¡��˵�����롰�ļ����˵�
		menu1.add(menuItemSave); //�������桱�˵�����롰�ļ����˵�
		menu2.add(menuItemCut); //�������С��˵�����롰�༭���˵�
		menu2.add(menuItemPaste); //����ճ�����˵�����롰�༭���˵�
		menu4.add(menuItemAbout); //�������ڡ��˵�����롰�������˵�
		//�����ǽ��˵����뵽�˵�����
		menubar.add(menu1);//�����ļ����˵�����˵���
		menubar.add(menu2);//�����༭���˵�����˵���
		menubar.add(menu3);//�����������˵�����˵���
		menubar.add(menu4);//�����������˵�����˵���
		
		setJMenuBar(menubar);//���ô��ڲ˵���
		setLocation(100, 300);//����λ��
		setSize(300, 200);//���ڴ�С
		setVisible(true);//���ڿɼ�
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}

public class Example9_03
{
	public static void main(String[] args)
	{//����������ʼ��
		new FrameWithMenu().init("Java �˵����");
	}
}
