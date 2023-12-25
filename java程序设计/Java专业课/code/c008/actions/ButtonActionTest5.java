package C011_SwingGui.event;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 * project_name: Java_Ex
 *
 * package_name: C011_SwingGui.event 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-4 ÉÏÎç10:17:45 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ButtonActionTest5.java  
 *
 * Description:  
 *
 */
public class ButtonActionTest5 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		ButtonFrame5 frame = new ButtonFrame5();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with a button panel
 */
class ButtonFrame5 extends JFrame {
	/**
		 * 
		 */
	private static final long serialVersionUID = 5152603828600938373L;

	public ButtonFrame5() {
		setTitle("ButtonTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// add panel to frame

		ButtonPanel5 panel = new ButtonPanel5();
		add(panel);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;
}

/**
 * A panel with three buttons.
 */
class ButtonPanel5 extends JPanel{
	/**
		 * 
		 */
	private static final long serialVersionUID = -4386630301049611644L;

	public ButtonPanel5() {
		makeButton("yellow", Color.YELLOW);
		makeButton("blue", Color.BLUE);
		makeButton("red", Color.RED);		
	}
	
	void makeButton(String name, final Color backgroundColor)
	{
	   JButton button = new JButton(name);
	   add(button);
	   button.addActionListener(new
	      ActionListener()
	      {
	         public void actionPerformed(ActionEvent event)
	         {
	            setBackground(backgroundColor);
	         }
	      });
	}
}
