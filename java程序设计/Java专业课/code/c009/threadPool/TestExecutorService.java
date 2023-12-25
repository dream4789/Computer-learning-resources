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
* version Created Time��2021��1��5�� ����9:48:17
*
* FileName:Test.java
*
* Description:
*/


public class TestExecutorService {

	/**
	 * ʵ����ExecutorService executorService = Executors.newFixedThreadPool(5);
 
			executorService.execute(new Runnable() {
			    public void run() {
			        System.out.println("Asynchronous task");
			    }
			});
			 
			executorService.shutdown();
			˵��������ʹ�� newFixedThreadPool() ������������һ��ExecutorService ��
			���ﴴ����һ����������5���߳�������̳߳ء�Ȼ���� execute() �����д����첽�� Runnable �ӿڵ�ʵ�֣�
			���������� ExecutorService �е�ĳ���߳�ִ����� Runnable �̣߳�һ���̰߳�����ί�и� ExecutorService��
			���߳̾ͻ����ִ�������������޹ص���������
		ExecutorService��ʵ��
			ExecutorService �ӿ��� java.util.concurrent ����������ʵ���ࣺ
				ThreadPoolExecutor			ScheduledThreadPoolExecutor
			���Դ���ExecutorService ��Ҳ����ʹ�� Executors �������������������ﴴ����ExecutorService �����ӣ�
			
				ExecutorService executorService1 = Executors.newSingleThreadExecutor();
				ExecutorService executorService2 = Executors.newFixedThreadPool(10);
				ExecutorService executorService3 = Executors.newScheduledThreadPool(10);
		ExecutorService ʹ�÷���
			execute(Runnable)
				execute(Runnable)���� ����һ�� java.lang.Runnable ������Ϊ�������������첽�ķ�ʽִ����,
				ʹ�����ַ�ʽû�а취��ȡִ�� Runnable ֮��Ľ���������ϣ����ȡ����֮��ķ���ֵ���ͱ���ʹ�� ���� Callable 
				������ execute() ������
			submit(Runnable)
				���� submit(Runnable) ����һ�� Runnable ��ʵ����Ϊ���������ǻ᷵�� Future ����
				Future ������������ж� Runnable �Ƿ����ִ�У�
			submit(Callable)
				���� submit(Callable) �ͷ��� submit(Runnable) �Ƚ����ƣ����������������ǽ��ղ�ͬ�Ĳ������͡�
				Callable ��ʵ���� Runnable ��ʵ�������ƣ����� Callable �� call() �������Է���һ����������� Runnable.run() ���ܷ��ؽ����
			invokeAny(��)
				���� invokeAny() ����һ������ Callable ����ļ�����Ϊ���������ø÷������᷵�� Future ����
				���Ƿ��ؼ�����ĳһ�� Callable ����Ľ���������޷���֤����֮�󷵻صĽ������һ�� Callable��
				ֻ֪��������Щ Callable ��ִ�н����� Callable ����
				�������������ϻ����׳��쳣��������ȡ�������� Callable ��ִ�У�
				Callable �ķ���ֵ���Դӷ��� submit(Callable) ���ص� Future �����л�ȡ��
					Future future = executorService.submit(new Callable(){
					    public Object call() throws Exception {
					        System.out.println("Asynchronous Callable");
					        return "Callable Result";
					    }
					});
					 
					System.out.println("future.get() = " + future.get());
					��������
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
			invokeAll(��)
			
			
			shutdown()�� ExecutorService �������Ϲرգ����ǲ��ٽ����µ�����һ�����е��߳̽���ִ�е�ǰ����ExecutorServie �Ż���Ĺر�
			shutdownNow() �������ر� ExecutorService����������᳢�����Ϲر���������ִ�е����񣬲������������Ѿ��ύ���ǻ�û�����е����񡣵��Ƕ�������ִ�е������Ƿ��ܹ��ɹ��ر������޷���֤�ģ��п���������ı��رյ��ˣ�Ҳ�п�������ִ�е����������
	 * */
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		test4();
	}
	
	/**
	 * ExecutorService ������ʹ��
	 * 	Java�ṩ�������̳߳صĺô����ڣ�
			a. ���ô��ڵ��̣߳����ٶ��󴴽��������Ŀ��������ܼѡ�
			b. ����Ч������󲢷��߳��������ϵͳ��Դ��ʹ���ʣ�ͬʱ���������Դ���������������
			c. �ṩ��ʱִ�С�����ִ�С����̡߳����������Ƶȹ��ܡ�
		Javaͨ��Executors�ṩ�����̳߳أ��ֱ�Ϊ��
			new CachedThreadPool����һ���ɻ����̳߳أ�����̳߳س��ȳ���������Ҫ���������տ����̣߳����޿ɻ��գ����½��̡߳�
			new FixedThreadPool ����һ�������̳߳أ��ɿ����߳���󲢷������������̻߳��ڶ����еȴ���
			new ScheduledThreadPool ����һ�������̳߳أ�֧�ֶ�ʱ������������ִ�С�
			new SingleThreadExecutor ����һ�����̻߳����̳߳أ���ֻ����Ψһ�Ĺ����߳���ִ�����񣬱�֤����������ָ��˳��(FIFO, LIFO, ���ȼ�)ִ�С�
	 * */
	public static void test1(){
	// newCachedThreadPool:����һ���ɻ����̳߳أ�����̳߳س��ȳ���������Ҫ���������տ����̣߳����޿ɻ��գ����½��̡߳�	
		//�̳߳�Ϊ���޴󣬵�ִ�еڶ�������ʱ��һ�������Ѿ���ɣ��Ḵ��ִ�е�һ��������̣߳�������ÿ���½��̡߳�
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
		//newFixedThreadPool:����һ�������̳߳أ��ɿ����߳���󲢷������������̻߳��ڶ����еȴ�
		//�����̳߳صĴ�С��ø���ϵͳ��Դ�������á�
		//��Runtime.getRuntime().availableProcessors()*POOL_MULTIPLE
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
		//newScheduledThreadPool:����һ�������̳߳أ�֧�ֶ�ʱ������������ִ�С�
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
		//newSingleThreadExecutor:����һ�����̻߳����̳߳أ���ֻ����Ψһ�Ĺ����߳���ִ�����񣬱�֤����������ָ��˳��(FIFO, LIFO, ���ȼ�)ִ�С�
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
