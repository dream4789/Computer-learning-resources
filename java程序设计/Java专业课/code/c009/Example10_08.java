package ch10;
class ReadBook1 implements Runnable{ 
    private int pageCount = 0;  
    public void run(){  
        try {  
            while (pageCount<100) {  
                System.out.println(Thread.currentThread().getName()+" is reading!");  
                pageCount +=20;   //读20页书休息500ms
                Thread.sleep(500);  
            }  
         }  
        catch(InterruptedException e) {
        	System.out.println(Thread.currentThread().getName()+" read the first "+(pageCount-20)+" pages.");
        	System.out.println(Thread.currentThread().getName()+"'s reading was interrupted !");
        }
        }  
    }  
 
public class Example10_08 {  
    
  public static void main(String[] args) throws Exception{  
      //将任务交给线程t1和t2  
      Thread t1 = new Thread(new ReadBook1()); 
      Thread t2 = new Thread(new ReadBook1());
      t1.setName("Zhangsan"); t2.setName("Lisi");
      t1.start(); t2.start();
      //主线程运行1000ms之后中断线程t1  
      Thread.sleep(1000);     
      t1.interrupt();  
  }  
}   
