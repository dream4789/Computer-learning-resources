package ch10;
import java.util.concurrent.locks.*;
 class Ticket implements Runnable
 {
     int num = 100;
      //����������ReentrantLock��������Ļ���������Lock�ӿڵ�һ��ʵ��
     Lock loc = new ReentrantLock();  
      public void run()
     {
         while( true )
         {
                 loc.lock();     //��ȡ��
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
                     loc.unlock();        //�ͷ���
                }
         }
     }
 }
 
 class Example10_11 
 {
     public static void main(String[] args) 
     {
         //����Ŀ�����
         Ticket t = new  Ticket();
          //�����߳�
         Thread tt = new  Thread(t);
         Thread tt2 = new  Thread(t);
         Thread tt3 = new  Thread(t);
         Thread tt4 = new  Thread(t);
         //�����߳�
         tt.start();
         tt2.start();
         tt3.start();
         tt4.start();
     }
 }
