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
 * created Time: 2018-1-4 ÉÏÎç10:04:33 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ButtonActionTest2.java  
 *
 * Description:  
 *
 */
public class ButtonActionTest2 {

	public static void main(String[] args) {
		ButtonFrame2 frame = new ButtonFrame2();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with a button panel
 */
class ButtonFrame2 extends JFrame {
	/**
		 * 
		 */
	private static final long serialVersionUID = 5152603828600938373L;

	public ButtonFrame2() {
		setTitle("ButtonTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// add panel to frame

		ButtonPanel2 panel = new ButtonPanel2();
		add(panel);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;
}

/**
 * A panel with three buttons.
 */
class ButtonPanel2 extends JPanel {
	/**
		 * 
		 */
	private static final long serialVersionUID = -4386630301049611644L;

	public ButtonPanel2() {
		// create buttons

		JButton yellowButton = new JButton("Yellow");
		JButton blueButton = new JButton("Blue");
		JButton redButton = new JButton("Red");

		// add buttons to panel

		add(yellowButton);
		add(blueButton);
		add(redButton);
		
		ColorAction2 listener = new ColorAction2();
		yellowButton.addActionListener(listener);
		blueButton.addActionListener(listener);
		redButton.addActionListener(listener);
	}	
	
	private class ColorAction2 implements ActionListener {		

		public void actionPerformed(ActionEvent event) {
			String color = event.getActionCommand();
			if ("Yellow".equals(color))
				setBackground(Color.YELLOW);
			else if ("Blue".equals(color))
				setBackground(Color.BLUE);
			else if ("Red".equals(color))
				setBackground(Color.RED);
		}
	}
}
