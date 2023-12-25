package C007_MultiThread;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 
 * Created Time£º2013-12-1 ÉÏÎç10:01:42
 * 
 * Project Name£ºEx.Proj
 * 
 * @author DarlingKe
 * 
 * @version 1.0
 * 
 * @since JDK 1.7.0_15
 * 
 *        FileName£ºTicketSale4.java
 * 
 *        Description£º
 */
public class TicketSale4 {

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
		ThreadTest4 t=new ThreadTest4();
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();
	}
}

class ThreadTest4 implements Runnable {
	private int tickets = 100;
	private SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
	public void run() {
		boolean isdone=false;
		while (!isdone) {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if (tickets > 0)
				System.out.println(" CurrentTime is :("
						+ sdf.format(new Date()) + ") "
						+ Thread.currentThread().getName()
						+ " is 	salingticket " + tickets--);
			else {
				isdone=true;
			}
		}
	}
}
