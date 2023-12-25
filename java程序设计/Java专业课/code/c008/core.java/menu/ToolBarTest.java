package C011_SwingGui.menu;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JToolBar;

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.menu
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-1-8 ÉÏÎç9:54:49
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: ToolBarTest.java
 * 
 * Description:
 * 
 */

public class ToolBarTest {
	public static void main(String[] args) {
		ToolBarFrame frame = new ToolBarFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with a toolbar and menu for color changes.
 */
class ToolBarFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 2942101625081933778L;

	public ToolBarFrame() {
		setTitle("ToolBarTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// add a panel for color change

		panel = new JPanel();

		// set up actions

		Action blueAction = new ColorAction("Blue", new ImageIcon(getClass()
				.getResource("/resources/images/toolbar/blue-ball.gif")),
				Color.BLUE);
		Action yellowAction = new ColorAction("Yellow", new ImageIcon(
				getClass().getResource(
						"/resources/images/toolbar/yellow-ball.gif")),
				Color.YELLOW);
		Action redAction = new ColorAction("Red", new ImageIcon(getClass()
				.getResource("/resources/images/toolbar/red-ball.gif")),
				Color.RED);

		Action exitAction = new AbstractAction("Exit", new ImageIcon(getClass()
				.getResource("/resources/images/toolbar/exit.gif"))) {
			/**
			 * 
			 */
			private static final long serialVersionUID = 7472119924343328667L;

			public void actionPerformed(ActionEvent event) {
				System.exit(0);
			}
		};
		exitAction.putValue(Action.SHORT_DESCRIPTION, "Exit");

		// populate tool bar

		JToolBar bar = new JToolBar();
		bar.add(blueAction);
		bar.add(yellowAction);
		bar.add(redAction);
		bar.addSeparator();
		bar.add(exitAction);
		add(bar, BorderLayout.NORTH);

		// populate menu

		JMenu menu = new JMenu("Color");
		menu.add(yellowAction);
		menu.add(blueAction);
		menu.add(redAction);
		menu.add(exitAction);
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(menu);
		setJMenuBar(menuBar);
		add(panel,BorderLayout.CENTER);
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 200;

	private JPanel panel;

	/**
	 * The color action sets the background of the frame to a given color.
	 */
	class ColorAction extends AbstractAction {
		/**
	 * 
	 */
		private static final long serialVersionUID = 7968474753634280481L;

		public ColorAction(String name, Icon icon, Color c) {
			putValue(Action.NAME, name);
			putValue(Action.SMALL_ICON, icon);
			putValue(Action.SHORT_DESCRIPTION, name + " background");
			putValue("Color", c);
		}

		public void actionPerformed(ActionEvent event) {
			Color c = (Color) getValue("Color");
			panel.setBackground(c);
		}
	}
}