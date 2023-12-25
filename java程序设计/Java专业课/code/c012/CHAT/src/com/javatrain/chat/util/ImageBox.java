package com.javatrain.chat.util;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JLabel;

public class ImageBox extends JLabel {

	Image image;
	ImageIcon icon;
	String text;
	boolean isTextVisible = true;

	ImageBox(ImageIcon imageIcon) {
		icon = imageIcon;
		this.image = imageIcon.getImage();
	}

	public boolean isTextVisible() {
		return isTextVisible;
	}

	public void setTextVisible(boolean isTextVisible) {
		this.isTextVisible = isTextVisible;
	}

	public void setImage(Image image, String text) {
		this.image = image;
		this.text = text;
		this.repaint();
	}

	@Override
	public String getText() {
		// TODO Auto-generated method stub
		return this.text;
	}

	public ImageBox(String text, ImageIcon imageIcon) {
		icon = imageIcon;
		this.text = text;
		this.image = imageIcon.getImage();
		// setPreferredSize(new Dimension(5, 25));
	}

	@Override
	protected void paintComponent(Graphics g) {
		// TODO Auto-generated method stub
		// super.paintComponent(g);
		// System.out.println(this.getWidth());
		g
				.drawImage(image, (this.getWidth() - icon.getIconWidth()) / 2,
						5, this);
		if (isTextVisible) {
			g.drawString(text, (this.getWidth() - text.length()) / 2
					- text.length() * 3, icon.getIconHeight()
					+ (this.getHeight() - icon.getIconHeight()) / 2 + 7);
		}
	}
}