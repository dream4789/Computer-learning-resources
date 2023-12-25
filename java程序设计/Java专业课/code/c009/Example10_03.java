package ch10;
	import java.util.concurrent.Callable;  
	import java.util.concurrent.ExecutionException;  
	import java.util.concurrent.FutureTask;  
	  
	public class Example10_03  implements Callable<Integer>  
	{  
	  public static void main(String[] args)  
	     {  
	        Example10_03 ctt = new Example10_03 ();  
	        FutureTask<Integer> ft = new FutureTask<>(ctt);  
	        for(int i = 0;i < 10;i++)  
	        {  
	            System.out.println(Thread.currentThread().getName()+"��ѭ������i��ֵ"+i);  
	            if(i==20)  
	            {  
new Thread(ft,"�з���ֵ���߳�").start();  
	            }  
	        }  
	        try  
	        {  
	            System.out.println("���̵߳ķ���ֵ��"+ft.get());  //��ȡ�߳�ִ�н��
	        } catch (InterruptedException e)  
	        {  
	            e.printStackTrace();  
	        } catch (ExecutionException e)  
	        {  
	            e.printStackTrace();  
	        }  
	  }  
	  
	    @Override  
	    public Integer call() throws Exception    //�߳���
	    {  
	        int i = 0;  
	        for(;i<100;i++)  
	        {  
	            System.out.println(Thread.currentThread().getName()+" "+i);  
	        }  
	        return i;  
	    }  
	 }  
