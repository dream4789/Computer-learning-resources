package ch10;
public class Example10_09 extends Thread {
    private volatile boolean isShutdownRequested = false;

    public final void shutdown(){
        isShutdownRequested = true;
        interrupt();
    }

    public final boolean isShutdownRequested() {
        return isShutdownRequested;
    }
    
    protected void doWork() throws InterruptedException {
        System.out.println("running...");
        sleep(500);
    }
    protected void doShutdown() {
        System.out.println("shutdown!");
    }

    @Override
    public void run() {
        try {
            while(!isShutdownRequested()){
                doWork();
            }
        } catch (InterruptedException e) {
            System.out.println("InterruptedException is Thrown");
        } finally {
            doShutdown();
        }
    }

    public static void main(String[] args) {
        Example10_09 thread = new Example10_09()  ;
        thread.start();

        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("即将调用shutdown()方法");
        thread.shutdown();
    }
}
