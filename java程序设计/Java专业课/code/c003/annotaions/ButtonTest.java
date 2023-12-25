package C012_Annotations;

/**
 * project_name: Java_Ex
 *
 * package_name: C012_Annotations 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-14 ÉÏÎç9:41:45 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: ButtonTest.java  
 *
 * Description:  
 *
 */
import java.awt.Color;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class ButtonTest {
	public static void main(String[] args) {
		ButtonFrame frame = new ButtonFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with a button panel
 */
class ButtonFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 7057939386306440824L;

	public ButtonFrame() {
		setTitle("ButtonTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		panel = new JPanel();
		add(panel);

		// create buttons

		yellowButton = new JButton("Yellow");
		blueButton = new JButton("Blue");
		redButton = new JButton("Red");

		// add buttons to panel

		panel.add(yellowButton);
		panel.add(blueButton);
		panel.add(redButton);

		ActionListenerInstaller.processAnnotations(this);
	}

	@ActionListenerFor(source = "yellowButton")
	public void yellowBackground() {
		panel.setBackground(Color.YELLOW);
	}

	@ActionListenerFor(source = "blueButton")
	public void blueBackground() {
		panel.setBackground(Color.BLUE);
	}

	@ActionListenerFor(source = "redButton")
	public void redBackground() {
		panel.setBackground(Color.RED);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;

	private JPanel panel;
	private JButton yellowButton;
	private JButton blueButton;
	private JButton redButton;
}
