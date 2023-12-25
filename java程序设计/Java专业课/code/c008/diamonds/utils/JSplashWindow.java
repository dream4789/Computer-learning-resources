package games.diamonds.utils;


import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

/**
 * <p>Title: JSplashWindow</p>
 * <p>Description: start up window</p>
 * <p>Copyright: Copyright (c) 2005</p>
 * <p>Company: Ahut</p>
 * @author Darling Ke
 * @version beta
 */
 
public class JSplashWindow extends JWindow {
	
	private static final long serialVersionUID=0L;
	
	private static JSplashWindow csw;
	private Image image;
	private String user;
	private String lab;
	private int x1 = 155;
	private int y1 = 220;
	private int x2 = 250;
	private int y2 = 235;
	private DisposeAdapter da;
	
	/**
	 *constructor
	 */	
    private JSplashWindow(String u, ImageIcon icon) {

		setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
		image = icon.getImage();
		user = u;
		setAlwaysOnTop(true);

		setSize(icon.getIconWidth(),icon.getIconHeight());
		Dimension screen = getToolkit().getScreenSize();
		setLocation((screen.width-getSize().width)/2, (screen.height-getSize().height)/2);
		this.setVisible(true);
		/**
		 * Note: To avoid that method splash hangs, we must set paintCalled to
		 * true and call notifyAll. This is necessary because the mouse click
		 * may occur before the contents of the window has been painted.
		 */
		MouseAdapter disposeOnClick = new MouseAdapter() {
			public void mouseClicked(MouseEvent evt) {
				/**
				 * synchronized(SplashWindow.this) {
				 * SplashWindow.this.paintCalled = true;
				 * SplashWindow.this.notifyAll(); }
				 */
				dispose();
			}
		};
		addMouseListener(disposeOnClick);
		/**
		 * setCloseOnClick(true);
		 */
    }
    
    /**
	 * set close on click use as about dialog
	 */
    public void setCloseOnClick(boolean b) {
    	if(b) {
    		if(da==null)
    			da = new DisposeAdapter();
    		addMouseListener(da);
    	} else if(da!=null) {
   			this.removeMouseListener(da);
    	}
    }
    
    /**
     *set the place where user name will be show
     */
    public void setUserLocation(int x,int y) {
    	x1 = x;
    	y1 = y;
    }
    
    /**
     *set the place where status will be show
     */
    public void setStatusLocation(int x,int y) {
    	x2 = x;
    	y2 = y;
    }
	
	/**
	 *paint
	 */
	public void paint(Graphics g) {
		g.drawImage(image,0,0,this);
		g.drawString("This product is licensed to: "+user,x1-150,y1);
		g.drawString("CopyRight@ 1996-2007 AHUT", x1-150,y1+15);
		if(lab!=null)
			g.drawString(lab,x2,y2);
	}
    
    /**
     *set the status text
     */
    public void setText(String lab) {
    	this.lab = lab;
    	repaint();
    }
    
    /**
     *inner class
     *to close the JWindow on click
     */
    private class DisposeAdapter extends MouseAdapter {
    	
    	public void mouseClicked(MouseEvent me) {
    		dispose();
    	}
    }
    
    /**
     *static method to set the instance
     *only once is premitted
     */
    public static synchronized boolean setInstance(String user,ImageIcon icon) {
    	if(csw==null) {
    		csw = new JSplashWindow(user,icon);
    		return true;
    	}
    	return false;
    }
    
    /**
     *get the instance of JSplashWindow
     *@return JSplashWindow
     */
    public static synchronized JSplashWindow getInstance() {
        return csw;
    }
}