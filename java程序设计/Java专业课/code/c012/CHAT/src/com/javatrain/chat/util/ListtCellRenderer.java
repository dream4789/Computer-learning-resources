package com.javatrain.chat.util;

import java.awt.Color;
import java.awt.Component;

import javax.swing.BorderFactory;
import javax.swing.DefaultListCellRenderer;
import javax.swing.JList;

public class ListtCellRenderer extends DefaultListCellRenderer {

	@Override
	public Component getListCellRendererComponent(JList list, Object value,
			int index, boolean isSelected, boolean cellHasFocus) {
		// TODO Auto-generated method stub
		/*
		 * return super.getListCellRendererComponent(list, value, index,
		 * isSelected, cellHasFocus);
		 */
		if (value instanceof User) {
			User user = (User) value;
			// this.setIcon(ImageFactory.getInstance().getImageIndex(user.getUserIcon()));
			this.setIcon(ImageFactory.getInstance().getImageIndex(
					user.getUserIcon()));
			this.setText(user.toString());
			this.setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1,
					Color.GRAY));
			String s = value.toString();
			setText(s);
			if (isSelected) {
				setBackground(list.getSelectionBackground());
				setForeground(list.getSelectionForeground());
			} else {
				setBackground(list.getBackground());
				setForeground(list.getForeground());
			}
			setEnabled(list.isEnabled());
			setFont(list.getFont());
			setOpaque(true);
		}
		return this;
	}

}
