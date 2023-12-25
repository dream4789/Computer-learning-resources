package C011_SwingGui.advanced.jtree;

import java.awt.Container;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.advanced
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-1-4 ÉÏÎç8:42:49
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: JTreeTest.java
 * 
 * Description:
 * 
 */
public class JTreeTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame frame = new SimpleTreeFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

}

class SimpleTreeFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public SimpleTreeFrame() {
		setTitle("SimpleTree");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// set up tree model data

		DefaultMutableTreeNode root = new DefaultMutableTreeNode("World");
		DefaultMutableTreeNode country = new DefaultMutableTreeNode("USA");
		root.add(country);
		DefaultMutableTreeNode state = new DefaultMutableTreeNode("California");
		country.add(state);
		DefaultMutableTreeNode city = new DefaultMutableTreeNode("San Jose");
		state.add(city);
		city = new DefaultMutableTreeNode("Cupertino");
		state.add(city);
		state = new DefaultMutableTreeNode("Michigan");
		country.add(state);
		city = new DefaultMutableTreeNode("Ann Arbor");
		state.add(city);
		country = new DefaultMutableTreeNode("Germany");
		root.add(country);
		state = new DefaultMutableTreeNode("Schleswig-Holstein");
		country.add(state);
		city = new DefaultMutableTreeNode("Kiel");
		state.add(city);

		// construct tree and put it in a scroll pane

		JTree tree = new JTree(root);
		Container contentPane = getContentPane();
		contentPane.add(new JScrollPane(tree));
	}

	private static final int DEFAULT_WIDTH = 300;
	private static final int DEFAULT_HEIGHT = 200;
}
