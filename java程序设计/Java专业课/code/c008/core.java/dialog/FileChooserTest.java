package C011_SwingGui.dialog;

import java.awt.Dimension;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileView;

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.dialog
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-1-3 ÏÂÎç4:48:23
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: FileChooserTest.java
 * 
 * Description:
 * 
 */
public class FileChooserTest {
	public static void main(String[] args) {
		ImageViewerFrame frame = new ImageViewerFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * A frame that has a menu for loading an image and a display area for the
 * loaded image.
 */
class ImageViewerFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = -5485449576538388096L;

	public ImageViewerFrame() {
		setTitle("FileChooserTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		// set up menu bar
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);

		JMenu menu = new JMenu("File");
		menuBar.add(menu);

		JMenuItem openItem = new JMenuItem("Open");
		menu.add(openItem);
		openItem.addActionListener(new FileOpenListener());

		JMenuItem exitItem = new JMenuItem("Exit");
		menu.add(exitItem);
		exitItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				System.exit(0);
			}
		});

		// use a label to display the images
		label = new JLabel();
		add(label);

		// set up file chooser
		chooser = new JFileChooser();

		// accept all image files ending with .jpg, .jpeg, .gif
		final ExtensionFileFilter filter = new ExtensionFileFilter();
		filter.addExtension("jpg");
		filter.addExtension("jpeg");
		filter.addExtension("gif");
		filter.setDescription("Image files");
		chooser.setFileFilter(filter);

		chooser.setAccessory(new ImagePreviewer(chooser));

		chooser.setFileView(new FileIconView(filter, new ImageIcon(
				getClass().getResource(
						"/resources/images/dialog/palette.gif"))));
	}

	/**
	 * This is the listener for the File->Open menu item.
	 */
	private class FileOpenListener implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			chooser.setCurrentDirectory(new File("."));

			// show file chooser dialog
			int result = chooser.showOpenDialog(ImageViewerFrame.this);

			// if image file accepted, set it as icon of the label
			if (result == JFileChooser.APPROVE_OPTION) {
				String name = chooser.getSelectedFile().getPath();
				label.setIcon(new ImageIcon(name));
			}
		}
	}

	public static final int DEFAULT_WIDTH = 300;
	public static final int DEFAULT_HEIGHT = 400;

	private JLabel label;
	private JFileChooser chooser;
}

/**
 * This file filter matches all files with a given set of extensions.
 */
class ExtensionFileFilter extends FileFilter {
	/**
	 * Adds an extension that this file filter recognizes.
	 * 
	 * @param extension
	 *            a file extension (such as ".txt" or "txt")
	 */
	public void addExtension(String extension) {
		if (!extension.startsWith("."))
			extension = "." + extension;
		extensions.add(extension.toLowerCase());
	}

	/**
	 * Sets a description for the file set that this file filter recognizes.
	 * 
	 * @param aDescription
	 *            a description for the file set
	 */
	public void setDescription(String aDescription) {
		description = aDescription;
	}

	/**
	 * Returns a description for the file set that this file filter recognizes.
	 * 
	 * @return a description for the file set
	 */
	public String getDescription() {
		return description;
	}

	public boolean accept(File f) {
		if (f.isDirectory())
			return true;
		String name = f.getName().toLowerCase();

		// check if the file name ends with any of the extensions
		for (String extension : extensions)
			if (name.endsWith(extension))
				return true;
		return false;
	}

	private String description = "";
	private ArrayList<String> extensions = new ArrayList<String>();
}

/**
 * A file view that displays an icon for all files that match a file filter.
 */
class FileIconView extends FileView {
	/**
	 * Constructs a FileIconView.
	 * 
	 * @param aFilter
	 *            a file filter--all files that this filter accepts will be
	 *            shown with the icon.
	 * @param anIcon
	 *            --the icon shown with all accepted files.
	 */
	public FileIconView(FileFilter aFilter, Icon anIcon) {
		filter = aFilter;
		icon = anIcon;
	}

	public Icon getIcon(File f) {
		if (!f.isDirectory() && filter.accept(f))
			return icon;
		else
			return null;
	}

	private FileFilter filter;
	private Icon icon;
}

/**
 * A file chooser accessory that previews images.
 */
class ImagePreviewer extends JLabel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 6771704530697478598L;

	/**
	 * Constructs an ImagePreviewer.
	 * 
	 * @param chooser
	 *            the file chooser whose property changes trigger an image
	 *            change in this previewer
	 */
	public ImagePreviewer(JFileChooser chooser) {
		setPreferredSize(new Dimension(100, 100));
		setBorder(BorderFactory.createEtchedBorder());

		chooser.addPropertyChangeListener(new PropertyChangeListener() {
			public void propertyChange(PropertyChangeEvent event) {
				if (event.getPropertyName() == JFileChooser.SELECTED_FILE_CHANGED_PROPERTY) {
					// the user has selected a new file
					File f = (File) event.getNewValue();
					if (f == null) {
						setIcon(null);
						return;
					}

					// read the image into an icon
					ImageIcon icon = new ImageIcon(f.getPath());

					// if the icon is too large to fit, scale it
					if (icon.getIconWidth() > getWidth())
						icon = new ImageIcon(icon.getImage().getScaledInstance(
								getWidth(), -1, Image.SCALE_DEFAULT));

					setIcon(icon);
				}
			}
		});
	}
}
