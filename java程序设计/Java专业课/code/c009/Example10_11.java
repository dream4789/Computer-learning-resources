package ch10;
import java.util.concurrent.locks.*;
 class Ticket implements Runnable
 {
     int num = 100;
      //创建锁对象，ReentrantLock（可重入的互斥锁）是Lock接口的一个实现
     Lock loc = new ReentrantLock();  
      public void run()
     {
         while( true )
         {
                 loc.lock();     //获取锁
                 try
                 {
                     if( num > 0 )
                     {
                         System.out.println(Thread.currentThread().
getName()+"............."+num);
                         num--;
                     }
                     Thread.sleep(500);
                 }
                 catch(InterruptedException e) {}
                 finally
                {
                     loc.unlock();        //释放锁
                }
         }
     }
 }
 
 class Example10_11 
 {
     public static void main(String[] args) 
     {
         //创建目标对象
         Ticket t = new  Ticket();
          //创建线程
         Thread tt = new  Thread(t);
         Thread tt2 = new  Thread(t);
         Thread tt3 = new  Thread(t);
         Thread tt4 = new  Thread(t);
         //启动线程
         tt.start();
         tt2.start();
         tt3.start();
         tt4.start();
     }
 }
