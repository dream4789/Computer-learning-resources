package C011_SwingGui.choice;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.choice
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-1-3 ÏÂÎç6:32:44
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: RadioButtonTest.java
 * 
 * Description:
 * 
 */

public class RadioButtonTest {
	public static void main(String[] args) {
		RadioButtonFrame frame = new RadioButtonFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame with a sample text label and radio buttons for selecting font sizes.
 */
class RadioButtonFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = -6052827765818070359L;

	public RadioButtonFrame() {
		setTitle("RadioButtonTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// add the sample text label

		label = new JLabel("The quick brown fox jumps over the lazy dog.");
		label.setFont(new Font("Serif", Font.PLAIN, DEFAULT_SIZE));
		add(label, BorderLayout.CENTER);

		// add the radio buttons

		buttonPanel = new JPanel();
		group = new ButtonGroup();

		addRadioButton("Small", 8);
		addRadioButton("Medium", 12);
		addRadioButton("Large", 18);
		addRadioButton("Extra large", 36);

		add(buttonPanel, BorderLayout.SOUTH);
	}

	/**
	 * Adds a radio button that sets the font size of the sample text.
	 * 
	 * @param name
	 *            the string to appear on the button
	 * @param size
	 *            the font size that this button sets
	 */
	public void addRadioButton(String name, final int size) {
		boolean selected = size == DEFAULT_SIZE;
		JRadioButton button = new JRadioButton(name, selected);
		group.add(button);
		buttonPanel.add(button);

		// this listener sets the label font size

		ActionListener listener = new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				// size refers to the final parameter of the addRadioButton
				// method
				label.setFont(new Font("Serif", Font.PLAIN, size));
			}
		};

		button.addActionListener(listener);
	}

	public static final int DEFAULT_WIDTH = 400;
	public static final int DEFAULT_HEIGHT = 200;

	private JPanel buttonPanel;
	private ButtonGroup group;
	private JLabel label;

	private static final int DEFAULT_SIZE = 12;
}