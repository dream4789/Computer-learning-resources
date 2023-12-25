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
 * created Time: 2018-1-4 ÉÏÎç10:09:28 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ButtonActionTest4.java  
 *
 * Description:  Becoming Comfortable with Inner Classes
 *
 */
public class ButtonActionTest4 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		ButtonFrame4 frame = new ButtonFrame4();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with a button panel
 */
class ButtonFrame4 extends JFrame {
	/**
		 * 
		 */
	private static final long serialVersionUID = 5152603828600938373L;

	public ButtonFrame4() {
		setTitle("ButtonTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// add panel to frame

		ButtonPanel4 panel = new ButtonPanel4();
		add(panel);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;
}

/**
 * A panel with three buttons.
 */
class ButtonPanel4 extends JPanel{
	/**
		 * 
		 */
	private static final long serialVersionUID = -4386630301049611644L;

	public ButtonPanel4() {
		// create buttons

		JButton yellowButton = new JButton("Yellow");
		JButton blueButton = new JButton("Blue");
		JButton redButton = new JButton("Red");

		// add buttons to panel

		add(yellowButton);
		add(blueButton);
		add(redButton);		
		
		yellowButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				setBackground(Color.YELLOW);
			}
		});
		blueButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				setBackground(Color.BLUE);
			}
		});
		redButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				setBackground(Color.RED);
			}
		});
	}
}
