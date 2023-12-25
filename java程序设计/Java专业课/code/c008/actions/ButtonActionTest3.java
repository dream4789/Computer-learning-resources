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
 * created Time: 2018-1-4 ÉÏÎç10:07:15 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ButtonActionTest3.java  
 *
 * Description:  Turning Components (ButtonPanel3) into Event Listeners
 *
 */
public class ButtonActionTest3 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		ButtonFrame3 frame = new ButtonFrame3();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with a button panel
 */
class ButtonFrame3 extends JFrame {
	/**
		 * 
		 */
	private static final long serialVersionUID = 5152603828600938373L;

	public ButtonFrame3() {
		setTitle("ButtonTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// add panel to frame

		ButtonPanel3 panel = new ButtonPanel3();
		add(panel);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;
}

/**
 * A panel with three buttons.
 */
class ButtonPanel3 extends JPanel implements ActionListener {
	/**
		 * 
		 */
	private static final long serialVersionUID = -4386630301049611644L;

	public ButtonPanel3() {
		// create buttons

		JButton yellowButton = new JButton("Yellow");
		JButton blueButton = new JButton("Blue");
		JButton redButton = new JButton("Red");

		// add buttons to panel

		add(yellowButton);
		add(blueButton);
		add(redButton);		
		
		yellowButton.addActionListener(this);
		blueButton.addActionListener(this);
		redButton.addActionListener(this);
	}		

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		String color = e.getActionCommand();
		if ("Yellow".equals(color))
			setBackground(Color.YELLOW);
		else if ("Blue".equals(color))
			setBackground(Color.BLUE);
		else if ("Red".equals(color))
			setBackground(Color.RED);
	}
}

 