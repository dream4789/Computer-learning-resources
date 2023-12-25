package com.javatrain.chat.util;

import java.util.MissingResourceException;
import java.util.ResourceBundle;

public class ResourceBundler {
	
	public static ResourceBundle getResourceBundle() {
		if (bundle == null) {
			bundle = ResourceBundle.getBundle("resources.string");
		}
		return bundle;
	}
	
	public static String getString(String key) {
		String value = null;
		try {
			value = getResourceBundle().getString(key);
		} catch (MissingResourceException e) {
			System.out
					.println("java.util.MissingResourceException: Couldn't find value for: "
							+ key);
		}
		if (value == null) {
			value = "Could not find resource: " + key + "  ";
		}
		return value;
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println(getString("Login.Title"));
	}
	
	private static ResourceBundle bundle = null;
}
