package C011_SwingGui.advanced.jlist;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.ButtonGroup;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.advanced
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-1-4 ÉÏÎç8:43:08
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: JListTest.java
 * 
 * Description:
 * 
 */
public class JListTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame frame = new ListFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

}

class ListFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ListFrame() {
		setTitle("ListTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		String[] words = { "quick", "brown", "hungry", "wild", "silent",
				"huge", "private", "abstract", "static", "final" };

		wordList = new JList(words);
		wordList.setVisibleRowCount(4);
		JScrollPane scrollPane = new JScrollPane(wordList);

		listPanel = new JPanel();
		listPanel.add(scrollPane);
		wordList.addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent event) {
				Object[] values = wordList.getSelectedValues();

				StringBuilder text = new StringBuilder(prefix);
				for (int i = 0; i < values.length; i++) {
					String word = (String) values[i];
					text.append(word);
					text.append(" ");
				}
				text.append(suffix);

				label.setText(text.toString());
			}
		});
		
		wordList.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent evt) { 
				if (evt.getClickCount() == 2) { 
					JList source = (JList) evt.getSource(); 
					Object[] selection = source.getSelectedValues();
					for(Object o:selection){
						JOptionPane.showMessageDialog(ListFrame.this,o.toString());
					}
			    } 
			} 

		});

		buttonPanel = new JPanel();
		group = new ButtonGroup();
		makeButton("Vertical", JList.VERTICAL);
		makeButton("Vertical Wrap", JList.VERTICAL_WRAP);
		makeButton("Horizontal Wrap", JList.HORIZONTAL_WRAP);

		add(listPanel, BorderLayout.NORTH);
		label = new JLabel(prefix + suffix);
		add(label, BorderLayout.CENTER);
		add(buttonPanel, BorderLayout.SOUTH);
	}

	/**
	 * Makes a radio button to set the layout orientation.
	 * 
	 * @param label
	 *            the button label
	 * @param orientation
	 *            the orientation for the list
	 */
	private void makeButton(String label, final int orientation) {
		JRadioButton button = new JRadioButton(label);
		buttonPanel.add(button);
		if (group.getButtonCount() == 0)
			button.setSelected(true);
		group.add(button);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				wordList.setLayoutOrientation(orientation);
				listPanel.revalidate();
			}
		});
	}

	private static final int DEFAULT_WIDTH = 400;
	private static final int DEFAULT_HEIGHT = 300;
	private JPanel listPanel;
	private JList wordList;
	private JLabel label;
	private JPanel buttonPanel;
	private ButtonGroup group;
	private String prefix = "The ";
	private String suffix = "fox jumps over the lazy dog.";
}
