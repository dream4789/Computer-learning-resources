package games.diamonds.gui;

import games.diamonds.utils.ImageFactory;
import games.diamonds.utils.JSplashWindow;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("now begin loading MainFrame...");
		
		JSplashWindow.setInstance("Darling Ke", ImageFactory.getInstance()
				.getSplashImage());		
		
		MainFrame mainFrame = new MainFrame("Russia Blocks V1.0");
		mainFrame.setVisible(true);
		JSplashWindow.getInstance().dispose();
		
	}

}
