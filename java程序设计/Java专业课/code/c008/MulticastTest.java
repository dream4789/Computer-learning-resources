package C011_SwingGui.event;

/**
 * project_name: Java_Ex
 *
 * package_name: C011_SwingGui.event 
 *
 * author:  DarlingKe
 *
 * created Time: 2018-1-26 ÏÂÎç7:27:20 
 *
 * version: 1.0 
 *
 * since: JDK 1.7.0_15
 *
 * FileName: MulticastTest.java  
 *
 * Description:  
 *
 */
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class MulticastTest {
	public static void main(String[] args) {
		MulticastFrame frame = new MulticastFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with buttons to make and close secondary frames
 */
class MulticastFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public MulticastFrame() {
		setTitle("MulticastTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// add panel to frame

		MulticastPanel panel = new MulticastPanel();
		add(panel);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;
}

/**
 * A panel with buttons to create and close sample frames.
 */
class MulticastPanel extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public MulticastPanel() {
		// add "New" button

		JButton newButton = new JButton("New");
		add(newButton);
		final JButton closeAllButton = new JButton("Close all");
		add(closeAllButton);

		ActionListener newListener = new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				BlankFrame frame = new BlankFrame(closeAllButton);
				frame.setVisible(true);
			}
		};

		newButton.addActionListener(newListener);
	}
}

/**
 * A blank frame that can be closed by clicking a button.
 */
class BlankFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Constructs a blank frame
	 * 
	 * @param closeButton
	 *            the button to close this frame
	 */
	public BlankFrame(final JButton closeButton) {
		counter++;
		setTitle("Frame " + counter);
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		setLocation(SPACING * counter, SPACING * counter);

		closeListener = new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				closeButton.removeActionListener(closeListener);
				dispose();
			}
		};
		closeButton.addActionListener(closeListener);
	}

	private ActionListener closeListener;
	public static final int DEFAULT_WIDTH = 200;
	public static final int DEFAULT_HEIGHT = 150;
	public static final int SPACING = 40;
	private static int counter = 0;
}