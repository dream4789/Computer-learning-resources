package C011_SwingGui.dialog;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.dialog
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-1-3 ÏÂÎç5:03:56
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: DialogTest.java
 * 
 * Description:
 * 
 */

public class DialogTest {
	public static void main(String[] args) {
		DialogFrame frame = new DialogFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with a menu whose File->About action shows a dialog.
 */
class DialogFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 7552900711685788231L;

	public DialogFrame() {
		setTitle("DialogTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// construct a File menu

		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		JMenu fileMenu = new JMenu("File");
		menuBar.add(fileMenu);

		// add About and Exit menu items

		// The About item shows the About dialog

		JMenuItem aboutItem = new JMenuItem("About");
		aboutItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				if (dialog == null) // first time
					dialog = new AboutDialog(DialogFrame.this);
				dialog.setVisible(true); // pop up dialog
			}
		});
		fileMenu.add(aboutItem);

		// The Exit item exits the program

		JMenuItem exitItem = new JMenuItem("Exit");
		exitItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				System.exit(0);
			}
		});
		fileMenu.add(exitItem);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;

	private AboutDialog dialog;
}

/**
 * A sample modal dialog that displays a message and waits for the user to click
 * the Ok button.
 */
class AboutDialog extends JDialog {
	/**
	 * 
	 */
	private static final long serialVersionUID = -2732747683020450448L;

	public AboutDialog(JFrame owner) {
		super(owner, "About DialogTest", true);

		// add HTML label to center

		add(new JLabel(
				"<html><h1><i>Core Java</i></h1><hr>By Cay Horstmann and Gary Cornell</html>"),
				BorderLayout.CENTER);

		// Ok button closes the dialog

		JButton ok = new JButton("Ok");
		ok.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				setVisible(false);
			}
		});

		// add Ok button to southern border

		JPanel panel = new JPanel();
		panel.add(ok);
		add(panel, BorderLayout.SOUTH);

		setSize(250, 150);
	}
}
