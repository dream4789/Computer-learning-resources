package C007_MultiThread;
/**  

 * Created Time：2013-12-1 上午10:36:25  

 * Project Name：Ex.Proj  

 * @author DarlingKe  

 * @version 1.0   

 * @since JDK 1.7.0_15  

 * FileName：PCTest.java  

 * Description：  

 */
public class PCTest {

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
		BufferArea bufferArea = new BufferArea();
		// 两个厨师两个客户
		Producer p1 = new Producer(1, bufferArea);
		Producer p2 = new Producer(2, bufferArea);
		Customer c1 = new Customer(1, bufferArea);
		Customer c2 = new Customer(2, bufferArea);
		new Thread(p1).start();
		new Thread(p2).start();
		new Thread(c1).start();
		new Thread(c2).start();

	}

}
class Food {
	private String producer;

	public Food(String producer) {
		super();
		this.producer = producer;
	}

	@Override
	public String toString() {
		return producer;
	}
}

class BufferArea {
	private int index = 0;
	private Food[] foodArray = new Food[10];

	public synchronized void produce(int id, Food food) {
		System.out.println("缓冲区产品个数：" + index + " 个");
		while (index == foodArray.length) {
			System.out.println("缓冲区满，开始等等。。。。。。");
			try {
				this.wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		this.notify();
		foodArray[index] = food;
		index++;
		System.out.println(food);

	}

	public synchronized Food take(int id) {
		System.out.println("缓冲区产品个数：" + index + " 个");
		while (index == 0) {
			System.out.println("缓冲区空，开始等等。。。。。。");
			try {
				this.wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		this.notify();
		index--;
		System.out.println("第" + id + "个消费者消费了 -->" + foodArray[index]);
		return foodArray[index];
	}
}

class Producer implements Runnable {
	private BufferArea bufferArea;
	private int id;

	public Producer(int id,BufferArea bufferArea) {
		super();
		this.id = id;
		this.bufferArea = bufferArea;
	}

	@Override
	public void run() {
		boolean isdone=false;
		int count = 0;
		while(!isdone){
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			Food food = new Food("第" + id + "个生产者生产的食品,FOODID:"+count);
			count ++;
			bufferArea.produce(id,food);
			if(count == 100) isdone=true;
		}
	}
}

class Customer implements Runnable {
	private BufferArea bufferArea;
	private int id;
	public Customer(int id,BufferArea bufferArea) {
		super();
		this.id = id;
		this.bufferArea = bufferArea;
	}

	@Override
	public void run() {
		boolean isdone=false;
		int count = 0;
		while(!isdone){
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			bufferArea.take(id);			
			count ++;
			if(count == 100) isdone=true;
		}
	}
}


