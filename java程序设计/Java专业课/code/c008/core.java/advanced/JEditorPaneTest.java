package C011_SwingGui.advanced;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Stack;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.event.HyperlinkEvent;
import javax.swing.event.HyperlinkListener;

/**
 This program demonstrates how to display HTML documents
 in an editor pane.
 */

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.advanced
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-1-4 ÉÏÎç8:45:23
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: JEditorPaneTest.java
 * 
 * Description: This program demonstrates how to display HTML documents in an
 * editor pane.
 * 
 */
public class JEditorPaneTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame frame = new EditorPaneFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

}

/**
 * This frame contains an editor pane, a text field and button to enter a URL
 * and load a document, and a Back button to return to a previously loaded
 * document.
 */
class EditorPaneFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 4218373936586476031L;
	public EditorPaneFrame() {
		setTitle("EditorPaneTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		final Stack<String> urlStack = new Stack<String>();
		final JEditorPane editorPane = new JEditorPane();
		final JTextField url = new JTextField(30);

		// set up hyperlink listener

		editorPane.setEditable(false);
		editorPane.addHyperlinkListener(new HyperlinkListener() {
			public void hyperlinkUpdate(HyperlinkEvent event) {
				if (event.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
					try {
						// remember URL for back button
						urlStack.push(event.getURL().toString());
						// show URL in text field
						url.setText(event.getURL().toString());
						editorPane.setPage(event.getURL());
					} catch (IOException e) {
						editorPane.setText("Exception: " + e);
					}
				}
			}
		});

		// set up checkbox for toggling edit mode

		final JCheckBox editable = new JCheckBox();
		editable.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				editorPane.setEditable(editable.isSelected());
			}
		});

		// set up load button for loading URL

		ActionListener listener = new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				try {
					// remember URL for back button
					urlStack.push(url.getText());
					editorPane.setPage(url.getText());
				} catch (IOException e) {
					editorPane.setText("Exception: " + e);
				}
			}
		};

		JButton loadButton = new JButton("Load");
		loadButton.addActionListener(listener);
		url.addActionListener(listener);

		// set up back button and button action

		JButton backButton = new JButton("Back");
		backButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				if (urlStack.size() <= 1)
					return;
				try {
					// get URL from back button
					urlStack.pop();
					// show URL in text field
					String urlString = urlStack.peek();
					url.setText(urlString);
					editorPane.setPage(urlString);
				} catch (IOException e) {
					editorPane.setText("Exception: " + e);
				}
			}
		});

		add(new JScrollPane(editorPane), BorderLayout.CENTER);

		// put all control components in a panel

		JPanel panel = new JPanel();
		panel.add(new JLabel("URL"));
		panel.add(url);
		panel.add(loadButton);
		panel.add(backButton);
		panel.add(new JLabel("Editable"));
		panel.add(editable);

		add(panel, BorderLayout.SOUTH);
	}

	private static final int DEFAULT_WIDTH = 600;
	private static final int DEFAULT_HEIGHT = 400;
}
