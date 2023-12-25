package C007_MultiThread;

/**
 * 
 * Created Time£º2013-12-1 ÉÏÎç10:14:37
 * 
 * Project Name£ºEx.Proj
 * 
 * @author DarlingKe
 * 
 * @version 1.0
 * 
 * @since JDK 1.7.0_15
 * 
 *        FileName£ºSynchronizedTest.java
 * 
 *        Description£º
 */
public class SynchronizedTest {

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
		ThreadTest6 t=new ThreadTest6();
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();		
		new Thread(t).start();

	}

}

class ThreadTest6 implements Runnable {
	private int tickets = 100;
	String str = new String("");

	public void run() {
		boolean isdone=false;
		while (!isdone) {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			synchronized (str) {
				if (tickets > 0) {
					try {
						Thread.sleep(100);
					} catch (Exception e) {
						System.out.println(e.getMessage());
					}
					System.out.println(Thread.currentThread().getName()
							+ " is salingticket " + tickets--);
				}
				else {
					isdone=true;
				}
			}
		}
	}
}
