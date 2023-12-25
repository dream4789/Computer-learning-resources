package C011_SwingGui.event;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.EventListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * project_name: Java_Ex
 * 
 * package_name: C011_SwingGui.event
 * 
 * author: DarlingKe
 * 
 * created Time: 2018-1-27 上午10:20:28
 * 
 * version: 1.0
 * 
 * since: JDK 1.7.0_15
 * 
 * FileName: EventSourceTest2.java
 * 
 * Description:
 * 
 */
public class EventSourceTest2 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		EventSourceFrame2 frame = new EventSourceFrame2();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

}

class EventSourceFrame2 extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = -6508641407988668633L;

	public EventSourceFrame2() {
		setTitle("EventSourceTest2");
		setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

		final CountPanel panel = new CountPanel();
		add(panel);
		panel.addPropertyChangeListener(new PropertyChangeListener() {
			public void propertyChange(PropertyChangeEvent event) {
				JOptionPane.showMessageDialog(EventSourceFrame2.this,"You have clicked " + event.getNewValue() +" times.");				
			}
		});
	}

	public static final int DEFAULT_WIDTH = 400;
	public static final int DEFAULT_HEIGHT = 200;
}

class CountPanel extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = -5214900343393266861L;

	public CountPanel() {
		JButton clickButton = new JButton("单击模拟属性改变");
		clickButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				int oldCount = clickCount++;
				//JOptionPane.showMessageDialog(CountPanel.this,"You have clicked " + count +" times.");
				firePropertyChangeEvent(new PropertyChangeEvent(this, "clickCount",
						oldCount, clickCount));
			}
		});
		add(clickButton);
		
		final JButton clickButton2 = new JButton("启动线程模拟属性改变");
		clickButton2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				startThread();
			}
		});
		add(clickButton2);
		//startThread();
	}
	
	/**
	 * Adds a change listener
	 * 
	 * @param listener
	 *            the listener to add
	 */
	public void addPropertyChangeListener(PropertyChangeListener listener) {
		listenerList.add(PropertyChangeListener.class, listener);
	}

	/**
	 * Removes a change listener
	 * 
	 * @param listener
	 *            the listener to remove
	 */
	public void removePropertyChangeListener(PropertyChangeListener listener) {
		listenerList.remove(PropertyChangeListener.class, listener);
	}

	public void firePropertyChangeEvent(PropertyChangeEvent event) {
		EventListener[] listeners = listenerList
				.getListeners(PropertyChangeListener.class);
		for (EventListener l : listeners)
			((PropertyChangeListener) l).propertyChange(event);
	}

	public void startThread(){
		Thread tt= new Thread(new Runnable() {
			@Override
			public void run() {
				// TODO Auto-generated method stub
				while(true){
					int oldCount = clickCount++;
					firePropertyChangeEvent(new PropertyChangeEvent(this, "clickCount",
							oldCount, clickCount));
					try {
						Thread.sleep(5000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		});
		tt.start();
	}
	
	private static int clickCount = 0;
}
