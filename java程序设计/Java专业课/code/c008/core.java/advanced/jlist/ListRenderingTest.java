package C011_SwingGui.advanced.jlist;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ListCellRenderer;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.advanced.jlist
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-4-16 ÉÏÎç10:14:16
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: ListRenderingTest.java
 * 
 * Description:
 * 
 */
public class ListRenderingTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame frame = new ListRenderingFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

}

class ListRenderingFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ListRenderingFrame() {
		setTitle("ListRenderingTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		ArrayList<Font> fonts = new ArrayList<Font>();
		final int SIZE = 24;
		fonts.add(new Font("Serif", Font.PLAIN, SIZE));
		fonts.add(new Font("SansSerif", Font.PLAIN, SIZE));
		fonts.add(new Font("Monospaced", Font.PLAIN, SIZE));
		fonts.add(new Font("Dialog", Font.PLAIN, SIZE));
		fonts.add(new Font("DialogInput", Font.PLAIN, SIZE));
		fontList = new JList(fonts.toArray());
		fontList.setVisibleRowCount(4);
		fontList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		fontList.setCellRenderer(new FontCellRenderer());
		JScrollPane scrollPane = new JScrollPane(fontList);

		JPanel p = new JPanel();
		p.add(scrollPane);
		fontList.addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent evt) {
				Font font = (Font) fontList.getSelectedValue();
				text.setFont(font);
			}

		});

		Container contentPane = getContentPane();
		contentPane.add(p, BorderLayout.SOUTH);
		text = new JTextArea("The quick brown fox jumps over the lazy dog");
		text.setFont((Font) fonts.get(0));
		text.setLineWrap(true);
		text.setWrapStyleWord(true);
		contentPane.add(text, BorderLayout.CENTER);
	}

	private JTextArea text;
	private JList fontList;
	private static final int DEFAULT_WIDTH = 400;
	private static final int DEFAULT_HEIGHT = 300;
}

/**
 * A cell renderer for Font objects that renders the font name in its own font.
 */
class FontCellRenderer extends JPanel implements ListCellRenderer {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public Component getListCellRendererComponent(JList list, Object value,
			int index, boolean isSelected, boolean cellHasFocus) {
		font = (Font) value;
		background = isSelected ? list.getSelectionBackground() : list
				.getBackground();
		foreground = isSelected ? list.getSelectionForeground() : list
				.getForeground();
		foreground=Color.GREEN;
		return this;
	}

	public void paintComponent(Graphics g) {
		String text = font.getFamily();
		FontMetrics fm = g.getFontMetrics(font);
		g.setColor(background);
		g.fillRect(0, 0, getWidth(), getHeight());
		g.setColor(foreground);
		g.setFont(font);
		g.drawString(text, 0, fm.getAscent());
	}

	public Dimension getPreferredSize() {
		String text = font.getFamily();
		Graphics g = getGraphics();
		FontMetrics fm = g.getFontMetrics(font);
		return new Dimension(fm.stringWidth(text), fm.getHeight());
	}

	private Font font;
	private Color background;
	private Color foreground;
}
