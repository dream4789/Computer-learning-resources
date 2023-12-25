package C007_MultiThread;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 
 * Created Time��2013-12-1 ����9:56:15
 * 
 * Project Name��Ex.Proj
 * 
 * @author DarlingKe
 * 
 * @version 1.0
 * 
 * @since JDK 1.7.0_15
 * 
 *        FileName��TicketSale2.java
 * 
 *        Description��
 */
public class TicketSale2 {

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
		new ThreadTest2().start();
		new ThreadTest2().start();
		new ThreadTest2().start();
		new ThreadTest2().start(); 
	}

}

class ThreadTest2 extends Thread {
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
						+ Thread.currentThread().getName()
						+ " is 	salingticket " + tickets--);
		}
	}
}
