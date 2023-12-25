import java.io.*;
public class FileLockTest {
   public static void main(String args[]) {
      File file=new File("Example11_15.java");
      WindowFileLock win=new WindowFileLock(file);
      win.setTitle("使用文件锁");
   }
}
