package com.javatrain.chat.util;

import java.awt.Image;
import java.awt.Toolkit;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import javax.swing.ImageIcon;

public class ImageFactory {

	private static ImageFactory imagefactory;
	private static ImageIcon images[], iconImages;

	private List<ImageIcon> imageIconList = new ArrayList<ImageIcon>();
	private HashMap<String, ImageIcon> hm_imageIcon = new HashMap<String, ImageIcon>();
	private HashMap<String, ImageIcon> hm_insertIcon = new HashMap<String, ImageIcon>();
	URLClassLoader loader = null;

	private ImageFactory() {
		try {
			images = new ImageIcon[54];
			loader = (URLClassLoader) getClass().getClassLoader();
			iconImages = new ImageIcon(loader.getResource("images/icon.gif"));
			loadResourece();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	private void loadResourece() {
		// TODO Auto-generated method stub
		Toolkit toolkit = Toolkit.getDefaultToolkit();
		ImageIcon image = null;
		for (int i = 1; i <= 30; i++) {
			// 获取资源并保存
			image = new ImageIcon(loader.getResource("images/"+i+".png"));
			hm_imageIcon.put(i+"", image);
		}
		for (int i = 1; i <= 30; i++) {
			// 获取资源并保存
			image = new ImageIcon(loader.getResource("images/"+i+".gif"));
			hm_insertIcon.put(i+"", image);
		}
		
	}

	public ImageIcon getIconImage() {
		return iconImages;
	}

	
	/*
	 * public ImageIcon getImageicon(int i) { return images[i]; }
	 */
//选择用户图标
	public ImageIcon getImageIndex(String key){
		return hm_imageIcon.get(key);
	}
	//插入图标
	public ImageIcon getinsertIcon(String key) {
		return hm_insertIcon.get(key);
	}	
	
	public ImageIcon getImageicon(int i) {
		return imageIconList.get(i);
	}

	public static synchronized ImageFactory getInstance() {
		if (imagefactory != null) {
			return imagefactory;
		} else {
			imagefactory = new ImageFactory();
			return imagefactory;
		}
	}

	public List<ImageIcon> getimageIconList() {
		return imageIconList;
	}

	public HashMap<String, ImageIcon> getHm_imageIcon() {
		return hm_imageIcon;
	}

	public HashMap<String, ImageIcon> getHm_insertIcon() {
		return hm_insertIcon;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println(ImageFactory.getInstance().getHm_insertIcon().size());
	}

}
