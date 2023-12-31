package com.javatrain.chat.gui;

import java.awt.BorderLayout;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.dnd.DnDConstants;
import java.awt.dnd.DragGestureEvent;
import java.awt.dnd.DragGestureListener;
import java.awt.dnd.DragSource;
import java.awt.dnd.DragSourceAdapter;
import java.awt.dnd.DragSourceDropEvent;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;

/**
 * This is a sample drag source for testing purposes. It consists of a list of
 * files in the current directory.
 */
public class DragSourceTest {
	public static void main(String[] args) {
		JFrame frame = new DragSourceFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 * This frame contains a list of files in the current directory with support for
 * dragging files to a drop target. Moved files are removed from the list.
 */
class DragSourceFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public DragSourceFrame() {
		setTitle("DragSourceTest");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		File f = new File(".").getAbsoluteFile();
		File[] files = f.listFiles();
		model = new DefaultListModel();
		for (File file : files)
			try {
				model.addElement(file.getCanonicalFile());
			} catch (IOException e) {
				JOptionPane.showMessageDialog(this, e);
			}
		fileList = new JList(model);
		add(new JScrollPane(fileList), BorderLayout.CENTER);
		add(new JLabel("Drag files from this list"), BorderLayout.NORTH);

		DragSource dragSource = DragSource.getDefaultDragSource();
		dragSource.createDefaultDragGestureRecognizer(fileList,
				DnDConstants.ACTION_COPY_OR_MOVE, new DragGestureListener() {
					public void dragGestureRecognized(DragGestureEvent event) {
						draggedValues = fileList.getSelectedValues();
						Transferable transferable = new FileListTransferable(
								draggedValues);
						event.startDrag(null, transferable,
								new FileListDragSourceListener());
					}
				});
	}

	/**
	 * A drag source listener that removes moved files from the file list.
	 */
	private class FileListDragSourceListener extends DragSourceAdapter {
		public void dragDropEnd(DragSourceDropEvent event) {
			if (event.getDropSuccess()) {
				int action = event.getDropAction();
				if (action == DnDConstants.ACTION_MOVE) {
					for (Object v : draggedValues)
						model.removeElement(v);
				}
			}
		}
	}

	private JList fileList;
	private DefaultListModel model;
	private Object[] draggedValues;
	private static final int DEFAULT_WIDTH = 300;
	private static final int DEFAULT_HEIGHT = 200;
}

class FileListTransferable implements Transferable {
	public FileListTransferable(Object[] files) {
		fileList = new ArrayList<Object>(Arrays.asList(files));
	}

	public DataFlavor[] getTransferDataFlavors() {
		return flavors;
	}

	public boolean isDataFlavorSupported(DataFlavor flavor) {
		return Arrays.asList(flavors).contains(flavor);
	}

	public Object getTransferData(DataFlavor flavor)
			throws UnsupportedFlavorException {
		if (flavor.equals(DataFlavor.javaFileListFlavor))
			return fileList;
		else if (flavor.equals(DataFlavor.stringFlavor))
			return fileList.toString();
		else
			throw new UnsupportedFlavorException(flavor);
	}

	private static DataFlavor[] flavors = { DataFlavor.javaFileListFlavor,
			DataFlavor.stringFlavor };

	private java.util.List<Object> fileList;
}
