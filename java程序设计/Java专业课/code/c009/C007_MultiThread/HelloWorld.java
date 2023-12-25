package C007_MultiThread;

/**
 * 
 * Created Time£º2013-12-1 ÉÏÎç10:20:40
 * 
 * Project Name£ºEx.Proj
 * 
 * @author DarlingKe
 * 
 * @version 1.0
 * 
 * @since JDK 1.7.0_15
 * 
 *        FileName£ºHelloWorld.java
 * 
 *        Description£º
 */
public class HelloWorld {

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
		P t = new P();
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();
		new Thread(t).start();
	}

}

class P implements Runnable {
	private String s[] = { "hello", " ", "world", "!" };
	boolean isdone = false;
	String str = new String("");

	public void run() {
		while (!isdone) {
			synchronized (str) {
				System.out.println(Thread.currentThread().getName());
				for (int i = 0; i < 4; i++) {
					System.out.print(s[i]);
					try {
						Thread.sleep(100);
					} catch (Exception e) {
						System.out.println(e.getMessage());
					}
				}
				System.out.println();
				isdone = true;
			}
		}
	}
}
