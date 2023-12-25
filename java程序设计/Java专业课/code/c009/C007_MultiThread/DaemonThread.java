package C007_MultiThread;
/**  

 * Created Time£º2013-12-1 ÉÏÎç9:30:25  

 * Project Name£ºEx.Proj  

 * @author DarlingKe  

 * @version 1.0   

 * @since JDK 1.7.0_15  

 * FileName£ºDaemonThread.java  

 * Description£º  

 */
public class DaemonThread {

	/**
	
	 * <p>Title: main</p>
	
	 * <p>Description: </p>
	
	 * @param args
	
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ThreadTest t=new ThreadTest();
		Thread tt=new Thread(t);
		//tt.setDaemon(true);
		tt.start();
	}

}

class ThreadTest implements Runnable{
	public void run(){
		while(true){
			System.out.println(Thread.currentThread().getName()+" is running.");
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
} 

