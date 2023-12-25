package com.javatrain.chat.util;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JLabel;

public class IconBox extends JLabel {

	ImageIcon imageIcon;
	String iconName;


	public IconBox(String iconName, ImageIcon imageIcon) {
		super(imageIcon,JLabel.CENTER);
		this.imageIcon= imageIcon;
		this.iconName = iconName;
	}
}