package ch10;
class ReadBook1 implements Runnable{ 
    private int pageCount = 0;  
    public void run(){  
        try {  
            while (pageCount<100) {  
                System.out.println(Thread.currentThread().getName()+" is reading!");  
                pageCount +=20;   //��20ҳ����Ϣ500ms
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
      //�����񽻸��߳�t1��t2  
      Thread t1 = new Thread(new ReadBook1()); 
      Thread t2 = new Thread(new ReadBook1());
      t1.setName("Zhangsan"); t2.setName("Lisi");
      t1.start(); t2.start();
      //���߳�����1000ms֮���ж��߳�t1  
      Thread.sleep(1000);     
      t1.interrupt();  
  }  
}   
