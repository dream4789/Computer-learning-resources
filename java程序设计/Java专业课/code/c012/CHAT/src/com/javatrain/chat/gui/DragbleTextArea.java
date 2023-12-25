package com.javatrain.chat.gui;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.dnd.DnDConstants;
import java.awt.dnd.DropTarget;
import java.awt.dnd.DropTargetDragEvent;
import java.awt.dnd.DropTargetDropEvent;
import java.awt.dnd.DropTargetEvent;
import java.awt.dnd.DropTargetListener;
import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import javax.swing.JTextArea;

public class DragbleTextArea extends JTextArea implements DropTargetListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 5898974690315676982L;

	public DragbleTextArea(){
		new DropTarget(this, DnDConstants.ACTION_COPY_OR_MOVE, this);
	}
	@Override
	public void dragEnter(DropTargetDragEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void dragExit(DropTargetEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void dragOver(DropTargetDragEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@SuppressWarnings("unchecked")
	@Override
	public void drop(DropTargetDropEvent dtde)
	{
		try
		{
			@SuppressWarnings("unused")
			Transferable tr = dtde.getTransferable();

			if (dtde.isDataFlavorSupported(DataFlavor.javaFileListFlavor))
			{
				dtde.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
				System.out.println("file cp");
				List<File> list = (List<File>) (dtde.getTransferable()
						.getTransferData(DataFlavor.javaFileListFlavor));
				Iterator<File> iterator = list.iterator();
				while (iterator.hasNext())
				{
					File f = (File) iterator.next();
					this.setText(f.getAbsolutePath());
				}
				dtde.dropComplete(true);
				this.updateUI();
			} else
			{
				dtde.rejectDrop();
			}
		} catch (IOException ioe)
		{
			ioe.printStackTrace();
		} catch (UnsupportedFlavorException ufe)
		{
			ufe.printStackTrace();
		}
	}

	@Override
	public void dropActionChanged(DropTargetDragEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
