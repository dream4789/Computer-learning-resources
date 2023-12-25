package C007_MultiThread;
/**  

 * Created Time£º2013-12-9 ÏÂÎç6:06:08  

 * Project Name£ºEx.Proj  

 * @author DarlingKe  

 * @version 1.0   

 * @since JDK 1.7.0_15  

 * FileName£ºPhilosopher.java  

 * Description£º  

 */
public class Philosopher extends Thread{

	/**
	
	 * <p>Title: main</p>
	
	 * <p>Description: </p>
	
	 * @param args
	
	 */
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Philosopher p1 = new Philosopher(1);
		Philosopher p2 = new Philosopher(2);
		Philosopher p3 = new Philosopher(3);
		Philosopher p4 = new Philosopher(4);
		Philosopher p5 = new Philosopher(5);
		
		new Thread(p1).start();
		new Thread(p2).start();
		new Thread(p3).start();
		new Thread(p4).start();
		new Thread(p5).start();

	}
	Philosopher(int id)
	{
		this.id = id;
	}
	
	public void run(){
		while(true)
		{
			System.out.println("Philosopher "+ id + " is thinking");			
			try {				
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}		
			eat(id-1);
		}
	}
	
	private synchronized void eat(int id){
		max-=1;
		while(max<0)
		{
			try {
				wait();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		fork[id]-=1;
		while(fork[id]<0)
		{
			try {
				wait();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		fork[(id+1)%5]-=1;
		while(fork[(id+1)%5]<0)
		{
			try {
				wait();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		System.out.println("Philosopher "+ (id+1) + " is eating");
		fork[(id+1)%5]+=1;
		fork[id]+=1;
		max+=1;
		notifyAll();
	}

	int[] fork={1,1,1,1,1};
	int max=4;
	private int id;

}
