package C007_MultiThread;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 
 * Created Time£º2013-12-1 ÉÏÎç9:53:23
 * 
 * Project Name£ºEx.Proj
 * 
 * @author DarlingKe
 * 
 * @version 1.0
 * 
 * @since JDK 1.7.0_15
 * 
 *        FileName£ºTicketSale1.java
 * 
 *        Description£º
 */
public class TicketSale1 {

	/**
	 * 
	 * <p>
	 * Title: main
	 * </p>
	 * 
	 * <p>
	 * Description:
	 * </p>
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Current Thread is: "+Thread.currentThread().getName());
		ThreadTest1 t=new ThreadTest1();
		t.start();
		t.start();
		t.start();
		t.start();
	}

}

class ThreadTest1 extends Thread {
	private int tickets = 100;
	private SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");

	public void run() {
		while (true) {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if (tickets > 0)
				System.out.println(" CurrentTime is :("
						+ sdf.format(new Date()) + ") "
						+ "Current Thread is: "+ Thread.currentThread().getName()
						+ " salingticket " + tickets--);
		}
	}
}
