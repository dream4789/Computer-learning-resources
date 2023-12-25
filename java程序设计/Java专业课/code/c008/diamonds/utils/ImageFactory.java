package games.diamonds.utils;

import java.net.URLClassLoader;

import javax.swing.ImageIcon;

public class ImageFactory {

	private static ImageFactory imagefactory;
    private static ImageIcon images[],splashImages,iconImages;

    private ImageFactory() {
    	try{
        images = new ImageIcon[54];
        URLClassLoader loader = (URLClassLoader)getClass().getClassLoader();
        splashImages=new ImageIcon(loader.getResource("resources/images/splash.bmp"));
        iconImages=new ImageIcon(loader.getResource("resources/images/icon.gif"));
    	}catch(Exception ex){
    		ex.printStackTrace();
    	}
    }
    
    public ImageIcon getIconImage(){
    	return iconImages;
    }
    
    public ImageIcon getSplashImage(){
    	return splashImages;
    }

    public ImageIcon getImageicon(int i) {
        return images[i];
    }

    public static synchronized ImageFactory getInstance() {
        if(imagefactory != null) {
            return imagefactory;
        } else {
            imagefactory = new ImageFactory();
            return imagefactory;
        }
    }

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
