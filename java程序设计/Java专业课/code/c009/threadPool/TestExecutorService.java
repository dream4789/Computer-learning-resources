package C000_TEST;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

/**
* project_name:Java_Ex
*
* package_name:newfeature.jdk8.nio.httpserver
*
* author DarlingKe
* 
* version Created Time：2021年1月5日 下午9:48:17
*
* FileName:Test.java
*
* Description:
*/


public class TestExecutorService {

	/**
	 * 实例：ExecutorService executorService = Executors.newFixedThreadPool(5);
 
			executorService.execute(new Runnable() {
			    public void run() {
			        System.out.println("Asynchronous task");
			    }
			});
			 
			executorService.shutdown();
			说明，首先使用 newFixedThreadPool() 工厂方法创建一个ExecutorService ，
			这里创建了一个可以容纳5个线程任务的线程池。然后，向 execute() 方法中传递异步的 Runnable 接口的实现，
			这样做会让 ExecutorService 中的某个线程执行这个 Runnable 线程，一旦线程把任务委托给 ExecutorService，
			该线程就会继续执行与运行任务无关的其它任务。
		ExecutorService的实现
			ExecutorService 接口在 java.util.concurrent 包中有如下实现类：
				ThreadPoolExecutor			ScheduledThreadPoolExecutor
			可以创建ExecutorService ，也可以使用 Executors 工厂方法来创建，这里创建了ExecutorService 的例子：
			
				ExecutorService executorService1 = Executors.newSingleThreadExecutor();
				ExecutorService executorService2 = Executors.newFixedThreadPool(10);
				ExecutorService executorService3 = Executors.newScheduledThreadPool(10);
		ExecutorService 使用方法
			execute(Runnable)
				execute(Runnable)方法 接收一个 java.lang.Runnable 对象作为参数，并且以异步的方式执行它,
				使用这种方式没有办法获取执行 Runnable 之后的结果，如果你希望获取运行之后的返回值，就必须使用 接收 Callable 
				参数的 execute() 方法。
			submit(Runnable)
				方法 submit(Runnable) 接收一个 Runnable 的实现作为参数，但是会返回 Future 对象。
				Future 对象可以用于判断 Runnable 是否结束执行：
			submit(Callable)
				方法 submit(Callable) 和方法 submit(Runnable) 比较类似，但是区别在于它们接收不同的参数类型。
				Callable 的实例与 Runnable 的实例很类似，但是 Callable 的 call() 方法可以返回一个结果。方法 Runnable.run() 则不能返回结果。
			invokeAny(…)
				方法 invokeAny() 接收一个包含 Callable 对象的集合作为参数。调用该方法不会返回 Future 对象，
				而是返回集合中某一个 Callable 对象的结果，而且无法保证调用之后返回的结果是哪一个 Callable，
				只知道它是这些 Callable 中执行结束的 Callable 对象。
				如果任务运行完毕或者抛出异常，方法会取消其它的 Callable 的执行：
				Callable 的返回值可以从方法 submit(Callable) 返回的 Future 对象中获取：
					Future future = executorService.submit(new Callable(){
					    public Object call() throws Exception {
					        System.out.println("Asynchronous Callable");
					        return "Callable Result";
					    }
					});
					 
					System.out.println("future.get() = " + future.get());
					输出结果：
					ExecutorService executorService = Executors.newSingleThreadExecutor();
					Set<Callable<String>> callables = new HashSet<Callable<String>>();
					callables.add(new Callable<String>() {
					    public String call() throws Exception {
					        return "Task 1";
					    }
					});
					callables.add(new Callable<String>() {
					    public String call() throws Exception {
					        return "Task 2";
					    }
					});
					callables.add(new Callable<String>() {
					    public String call() throws Exception {
					        return "Task 3";
					    }
					});
					String result = executorService.invokeAny(callables);
					System.out.println("result = " + result);
					executorService.shutdown();
			invokeAll(…)
			
			
			shutdown()： ExecutorService 不会马上关闭，而是不再接收新的任务，一旦所有的线程结束执行当前任务，ExecutorServie 才会真的关闭
			shutdownNow() ：立即关闭 ExecutorService。这个方法会尝试马上关闭所有正在执行的任务，并且跳过所有已经提交但是还没有运行的任务。但是对于正在执行的任务，是否能够成功关闭它是无法保证的，有可能他们真的被关闭掉了，也有可能它会执行到任务结束。
	 * */
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		test4();
	}
	
	/**
	 * ExecutorService 的理解和使用
	 * 	Java提供的四种线程池的好处在于：
			a. 重用存在的线程，减少对象创建、消亡的开销，性能佳。
			b. 可有效控制最大并发线程数，提高系统资源的使用率，同时避免过多资源竞争，避免堵塞。
			c. 提供定时执行、定期执行、单线程、并发数控制等功能。
		Java通过Executors提供四种线程池，分别为：
			new CachedThreadPool创建一个可缓存线程池，如果线程池长度超过处理需要，可灵活回收空闲线程，若无可回收，则新建线程。
			new FixedThreadPool 创建一个定长线程池，可控制线程最大并发数，超出的线程会在队列中等待。
			new ScheduledThreadPool 创建一个定长线程池，支持定时及周期性任务执行。
			new SingleThreadExecutor 创建一个单线程化的线程池，它只会用唯一的工作线程来执行任务，保证所有任务按照指定顺序(FIFO, LIFO, 优先级)执行。
	 * */
	public static void test1(){
	// newCachedThreadPool:创建一个可缓存线程池，如果线程池长度超过处理需要，可灵活回收空闲线程，若无可回收，则新建线程。	
		//线程池为无限大，当执行第二个任务时第一个任务已经完成，会复用执行第一个任务的线程，而不用每次新建线程。
		ExecutorService cachedThreadPool = Executors.newCachedThreadPool();
		for (int i = 0; i < 10; i++) {
		    final int index = i;		    
//		    try {
//		        Thread.sleep(index * 100);
//		    } catch (InterruptedException e) {
//		        e.printStackTrace();
//		    }
		    cachedThreadPool.execute(new Runnable() {

		        @Override
		        public void run() {
		        	try {
				        Thread.sleep(index * 100);
				    } catch (InterruptedException e) {
				        e.printStackTrace();
				    }
		        	System.out.println(Thread.currentThread().getName());
		            System.out.println(index);
		        }
		    });
		}
		cachedThreadPool.shutdown();
	}

	public static void test2(){
		//newFixedThreadPool:创建一个定长线程池，可控制线程最大并发数，超出的线程会在队列中等待
		//定长线程池的大小最好根据系统资源进行设置。
		//如Runtime.getRuntime().availableProcessors()*POOL_MULTIPLE
		ExecutorService fixedThreadPool = Executors.newFixedThreadPool(4);
		for (int i = 0; i < 10; i++) {
		    final int index = i;
		    fixedThreadPool.execute(new Runnable() {

		        @Override
		        public void run() {
		            try {
		            	System.out.println(Thread.currentThread().getName());
		                System.out.println(index);
		                Thread.sleep(200);
		            } catch (InterruptedException e) {
		                // TODO Auto-generated catch block
		                e.printStackTrace();
		            }
		        }
		    });
		}
		fixedThreadPool.shutdown();
	}
	
	public static void test3(){
		//newScheduledThreadPool:创建一个定长线程池，支持定时及周期性任务执行。
		ScheduledExecutorService scheduledThreadPool = Executors.newScheduledThreadPool(5);
//		scheduledThreadPool.schedule(new Runnable() {
//
//		    @Override
//		    public void run() {
//		        System.out.println("delay 3 seconds");
//		    }
//		}, 3, TimeUnit.SECONDS);
		
		scheduledThreadPool.scheduleAtFixedRate(new Runnable() {
			@Override
			public void run() {
				System.out.println("delay 1 seconds, and excute every 3 seconds");
			}
		}, 1, 3, TimeUnit.SECONDS);
		scheduledThreadPool.shutdown();
	}

	public static void test4(){
		//newSingleThreadExecutor:创建一个单线程化的线程池，它只会用唯一的工作线程来执行任务，保证所有任务按照指定顺序(FIFO, LIFO, 优先级)执行。
		ExecutorService singleThreadExecutor = Executors.newSingleThreadExecutor();
		for (int i = 0; i < 10; i++) {
		    final int index = i;
		    singleThreadExecutor.execute(new Runnable() {

		        @Override
		        public void run() {
		            try {
		                System.out.println(index);
		                Thread.sleep(200);
		            } catch (InterruptedException e) {
		                // TODO Auto-generated catch block
		                e.printStackTrace();
		            }
		        }
		    });
		}
		singleThreadExecutor.shutdown();
	}
	
}
