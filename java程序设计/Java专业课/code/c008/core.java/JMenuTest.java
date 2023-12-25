package C011_SwingGui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPopupMenu;
import javax.swing.KeyStroke;

/**
 * project_name: Java_Ex
 *
 * package_name: C011_SwingGui 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-3 下午12:27:21 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: JMenuTest.java  
 *
 * Description:  
 *
 */
public class JMenuTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new JMenuFrame("Test JMenu");
	}

}

class JMenuFrame extends JFrame{
    /**
	 * 
	 */
	private static final long serialVersionUID = 1448591950870352597L;
	JMenuBar menubar;
    JMenu menu;
    JMenuItem printItem,saveItem;
    JPopupMenu popupMenu;
    String path = "/resources/images/";

	JMenuFrame(String s) {
		setTitle(s);
		setSize(400, 500);
		setLocation(120, 120);
		setVisible(true);
		menubar = new JMenuBar();
		menu = new JMenu("文件");

		printItem = new JMenuItem("打印", new ImageIcon(getClass().getResource(
				"/resources/images/menu/print.png")));
		printItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(JMenuFrame.this, "You Cicked PrintMenu", "Info",
						1);
			}
		});
		saveItem = new JMenuItem("保存", new ImageIcon(getClass().getResource(
				path + "menu/save.png")));
		saveItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(JMenuFrame.this, "You Cicked saveMenu", "Info",
						1);
			}
		});
		printItem.setAccelerator(KeyStroke.getKeyStroke("control O"));
		saveItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
				InputEvent.CTRL_MASK));
		menu.add(printItem);
		menu.addSeparator();
		menu.add(saveItem);
		menubar.add(menu);
		setJMenuBar(menubar);
		
		popupMenu = new JPopupMenu();
		JMenuItem rightMenuItem1 = new JMenuItem("右键菜单一");
		rightMenuItem1.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				JOptionPane.showMessageDialog(JMenuFrame.this, "You Cicked rightMenu One.", "Info",
						1);
			}
		});
		JMenuItem rightMenuItem2 = new JMenuItem("右键菜单二");
		rightMenuItem2.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				JOptionPane.showMessageDialog(JMenuFrame.this, "You Cicked rightMenu Two.", "Info",
						1);
			}
		});
		popupMenu.add(rightMenuItem1);
		popupMenu.add(rightMenuItem2);
		getContentPane().addMouseListener(new MouseAdapter(){
	        public void mousePressed(MouseEvent event)
	        {
	            if(event.isPopupTrigger())
	            	popupMenu.show(event.getComponent(),event.getX(),event.getY());
	        }
	        public void mouseReleased(MouseEvent event)
	        {
	            if(event.isPopupTrigger())
	            	popupMenu.show(event.getComponent(),event.getX(),event.getY());
	        }
	    });
		validate();
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	}
}



 