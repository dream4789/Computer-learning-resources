package C007_MultiThread;

import java.util.Random;

/**  

 * Created Time£º2013-12-7 ÏÂÎç7:19:52  

 * Project Name£ºEx.Proj  

 * @author DarlingKe  

 * @version 1.0   

 * @since JDK 1.7.0_15  

 * FileName£ºExCooperation.java  

 * Description£º  

 */
public class ExCooperation {

	/**
	
	 * <p>Title: main</p>
	
	 * <p>Description: </p>
	
	 * @param args
	
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		WorkStudent ws1= new WorkStudent(1,10);
		WorkStudent ws2= new WorkStudent(2,20);
		WorkStudent ws3= new WorkStudent(3,30);
		WorkStudent ws4= new WorkStudent(4,40);
		new Thread(ws1).start();
		new Thread(ws2).start();
		new Thread(ws3).start();
		new Thread(ws4).start();
	}

}

class WorkStudent implements Runnable {
	private long sleeptime;
	private int id;
	private static int[] desk={0,0,0,0,0},chair={0,0,0,0,0};
	public static int chairCount = 500;
	public static int deskCount = 500;
	String chairLock ="";
	String deskLock ="";
	
	public WorkStudent(int id,long time){
		super();
		this.id=id;
		this.sleeptime=time;
	}
	public void run() {
		boolean isDone = false;
		while(!isDone){
			try {
				Thread.sleep(sleeptime);
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			Random rdm = new Random(System.currentTimeMillis());
			if(rdm.nextInt() % 2 ==0){
				synchronized (chairLock) {
					if(chairCount>0){
						System.out.println("Student "+id+": wiping chair "+chairCount--);
						chair[id]+=1;
					}
				}
			}else{
				synchronized (deskLock) {
					if(deskCount>0){
						System.out.println("Student "+id+": wiping desk "+deskCount--);
						desk[id]+=1;
					}
				}
			}
			if(chairCount==0 && deskCount==0)
				isDone=true;
			if(isDone){				
				System.out.println("Result: Student "+id+" wiped "+desk[id]+" desks and "+chair[id]+" chairs.");				
			}
		}		
	}
}
