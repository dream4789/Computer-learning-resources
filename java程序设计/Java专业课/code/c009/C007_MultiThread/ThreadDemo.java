package C007_MultiThread;
/**  

 * Created Time£º2013-12-5 ÉÏÎç9:43:43  

 * Project Name£ºEx.Proj  

 * @author DarlingKe  

 * @version 1.0   

 * @since JDK 1.7.0_15  

 * FileName£ºThreadDemo.java  

 * Description£º  

 */
public class ThreadDemo {

	/**
	
	 * <p>Title: main</p>
	
	 * <p>Description: </p>
	
	 * @param args
	
	 */
	public static void main(String[] args) {
		MyThread mt= new MyThread();
		mt.start();	//mt.run();
		while(true){
			System.out.println("Main running!");
		}
	}

}

class MyThread extends Thread{
	public void run(){
		while(true){
			System.out.println("Thread running!");
		}
	}
}
