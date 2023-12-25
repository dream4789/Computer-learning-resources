package C007_MultiThread;

/**
 * 
 * Created Time£º2013-12-1 ÉÏÎç10:08:10
 * 
 * Project Name£ºEx.Proj
 * 
 * @author DarlingKe
 * 
 * @version 1.0
 * 
 * @since JDK 1.7.0_15
 * 
 *        FileName£ºNoSynchronized.java
 * 
 *        Description£º
 */
public class NoSynchronized {

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
		ThreadTest5 t=new ThreadTest5();
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();
	}

}

class ThreadTest5 implements Runnable {
	private int tickets = 100;

	public void run() {
		boolean isdone=false;
		while (!isdone) {
			if (tickets > 0) {
				try {
					Thread.sleep(100);
				} catch (Exception e) {
					System.out.println(e.getMessage());
				}
				System.out.println(Thread.currentThread().getName()
						+ " is salingticket" + tickets--);
			}
			else {
				isdone=true;
			}
		}
	}
}
