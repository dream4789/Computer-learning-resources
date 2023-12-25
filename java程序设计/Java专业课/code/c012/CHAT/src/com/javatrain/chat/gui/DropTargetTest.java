package com.javatrain.chat.gui;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.dnd.DnDConstants;
import java.awt.dnd.DropTarget;
import java.awt.dnd.DropTargetDragEvent;
import java.awt.dnd.DropTargetDropEvent;
import java.awt.dnd.DropTargetEvent;
import java.awt.dnd.DropTargetListener;
import java.io.File;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.UIManager;

/**
 This is a test class to test drag and drop behavior. Drop items into the text area to see the 
 MIME types of the drop target.
 */
public class DropTargetTest {
	public static void main(String[] args) {
		JFrame frame = new DropTargetFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

/**
 This frame contains a text area that is a simple drop target.
 */
class DropTargetFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public DropTargetFrame() {
		setTitle("DropTarget");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		try {
			UIManager
					.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
		} catch (Exception e) {
			e.printStackTrace();
		}
		JTextArea textArea = new JTextArea("Drop items into this text area.\n");

		new DropTarget(textArea, new TextDropTargetListener(textArea));
		add(new JScrollPane(textArea), "Center");
	}

	private static final int DEFAULT_WIDTH = 300;
	private static final int DEFAULT_HEIGHT = 300;
}

/**
 This listener displays the properties of a dropped object.
 */
class TextDropTargetListener implements DropTargetListener {
	/**
	   Constructs a listener.
	   @param aTextArea the text area in which to display the
	   properties of the dropped object.
	 */
	public TextDropTargetListener(JTextArea aTextArea) {
		textArea = aTextArea;
	}

	public void dragEnter(DropTargetDragEvent event) {
		int a = event.getDropAction();
		if ((a & DnDConstants.ACTION_COPY) != 0)
			textArea.append("ACTION_COPY\n");
		if ((a & DnDConstants.ACTION_MOVE) != 0)
			textArea.append("ACTION_MOVE\n");
		if ((a & DnDConstants.ACTION_LINK) != 0)
			textArea.append("ACTION_LINK\n");

		if (!isDragAcceptable(event)) {
			event.rejectDrag();
			return;
		}
	}

	public void dragExit(DropTargetEvent event) {
	}

	public void dragOver(DropTargetDragEvent event) {
		// you can provide visual feedback here
	}

	public void dropActionChanged(DropTargetDragEvent event) {
		if (!isDragAcceptable(event)) {
			event.rejectDrag();
			return;
		}
	}

	@SuppressWarnings("unchecked")
	public void drop(DropTargetDropEvent event) {
		if (!isDropAcceptable(event)) {
			event.rejectDrop();
			return;
		}

		event.acceptDrop(DnDConstants.ACTION_COPY);

		Transferable transferable = event.getTransferable();

		DataFlavor[] flavors = transferable.getTransferDataFlavors();
		for (int i = 0; i < flavors.length; i++) {
			DataFlavor d = flavors[i];
			textArea.append("MIME type=" + d.getMimeType() + "\n");

			try {
				if (d.equals(DataFlavor.javaFileListFlavor)) {
					java.util.List<File> fileList = (java.util.List<File>) transferable
							.getTransferData(d);
					for (File f : fileList) {
						textArea.append(f + "\n");
					}
				} else if (d.equals(DataFlavor.stringFlavor)) {
					String s = (String) transferable.getTransferData(d);
					textArea.append(s + "\n");
				}
			} catch (Exception e) {
				textArea.append(e + "\n");
			}
		}
		textArea.append("\n");
		event.dropComplete(true);
	}

	public boolean isDragAcceptable(DropTargetDragEvent event) {
		// usually, you check the available data flavors here
		// in this program, we accept all flavors
		return (event.getDropAction() & DnDConstants.ACTION_COPY_OR_MOVE) != 0;
	}

	public boolean isDropAcceptable(DropTargetDropEvent event) {
		// usually, you check the available data flavors here
		// in this program, we accept all flavors
		return (event.getDropAction() & DnDConstants.ACTION_COPY_OR_MOVE) != 0;
	}

	private JTextArea textArea;
}
