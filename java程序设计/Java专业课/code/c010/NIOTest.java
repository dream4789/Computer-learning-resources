package cn.ahut.edu.test;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.InetSocketAddress;
import java.net.URLDecoder;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.MappedByteBuffer;
import java.nio.channels.DatagramChannel;
import java.nio.channels.FileChannel;
import java.nio.channels.FileChannel.MapMode;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Date;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.Set;

/**
* project_name:Jetty6-core
*
* package_name:cn.ahut.edu.test
*
* author DarlingKe
* 
* version Created Time：2020年12月29日 下午7:35:11
*
* FileName:NIOTest.java
*
* Description:
*/
public class NIOTest {
	
	
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		test1();
	}
	
/**
* 一、缓冲区（Buffer）：在 Java NIO 中负责数据的存取。缓冲区就是数组。用于存储不同数据类型的数据	 * 
* 根据数据类型不同（boolean 除外），提供了相应类型的缓冲区：
	 * ByteBuffer
	 * CharBuffer
	 * ShortBuffer
	 * IntBuffer
	 * LongBuffer
	 * FloatBuffer
	 * DoubleBuffer	 * 
	 * 上述缓冲区的管理方式几乎一致，通过 allocate() 获取缓冲区
	 * 
* 二、缓冲区存取数据的两个核心方法：
	 * put() : 存入数据到缓冲区中
	 * get() : 获取缓冲区中的数据
	 * 
* 三、缓冲区中的四个核心属性：
	 * capacity : 容量，表示缓冲区中最大存储数据的容量。一旦声明不能改变。
	 * limit : 界限，表示缓冲区中可以操作数据的大小。（limit 后数据不能进行读写）
	 * position : 位置，表示缓冲区中正在操作数据的位置。	 * 
	 * mark : 标记，表示记录当前 position 的位置。可以通过 reset() 恢复到 mark 的位置	 * 
	 * 0 <= mark <= position <= limit <= capacity
	 * 
* 四、直接缓冲区与非直接缓冲区：
	 * 非直接缓冲区：通过 allocate() 方法分配缓冲区，将缓冲区建立在 JVM 的内存中
	 * 直接缓冲区：通过 allocateDirect() 方法分配直接缓冲区，将缓冲区建立在物理内存中。可以提高效率
* */
	public static void test3(){
        //分配直接缓冲区
        ByteBuffer buf = ByteBuffer.allocateDirect(1024);        
        System.out.println(buf.isDirect());
    }
	
	public static void test2(){
        String str = "abcde";        
        ByteBuffer buf = ByteBuffer.allocate(1024);
        
        buf.put(str.getBytes());        
        buf.flip();
        
        byte[] dst = new byte[buf.limit()];
        buf.get(dst, 0, 2);
        System.out.println(new String(dst, 0, 2));
        System.out.println("position:"+buf.position());
        
        //mark() : 标记
        buf.mark();        
        buf.get(dst, 2, 2);
        System.out.println(new String(dst, 2, 2));
        System.out.println("position:"+buf.position());
        
        //reset() : 恢复到 mark 的位置
        buf.reset();
        System.out.println("position:"+buf.position());
        
        //判断缓冲区中是否还有剩余数据
        if(buf.hasRemaining()){            
            //获取缓冲区中可以操作的数量
            System.out.println("remaining:"+buf.remaining());
        }
    }
	
	public static void test1(){
        String str = "哎比射迪Eabcde";
        
        //1. 分配一个指定大小的缓冲区
        ByteBuffer buf = ByteBuffer.allocate(1024);
        
        System.out.println("-----------------allocate()----------------");
        System.out.println("position:"+buf.position());
        System.out.println("limit:"+buf.limit());
        System.out.println("capacity:"+buf.capacity());
        
        //2. 利用 put() 存入数据到缓冲区中
        buf.put(str.getBytes());
        
        System.out.println("buf.put:"+str);
        System.out.println("-----------------put()----------------");
        System.out.println("position:"+buf.position());
        System.out.println("limit:"+buf.limit());
        System.out.println("capacity:"+buf.capacity());
        
        //3. 切换读取数据模式
        buf.flip();
        
        System.out.println("-----------------flip()----------------");
        System.out.println("position:"+buf.position());
        System.out.println("limit:"+buf.limit());
        System.out.println("capacity:"+buf.capacity());
        
        //4. 利用 get() 读取缓冲区中的数据
        byte[] dst = new byte[buf.limit()];
        buf.get(dst);
        System.out.println(new String(dst, 0, dst.length));
        
        System.out.println("-----------------get()----------------");
        System.out.println("position:"+buf.position());
        System.out.println("limit:"+buf.limit());
        System.out.println("capacity:"+buf.capacity());
        
        //5. rewind() : 可重复读
        buf.rewind();
        
        System.out.println("-----------------rewind()----------------");
        System.out.println("position:"+buf.position());
        System.out.println("limit:"+buf.limit());
        System.out.println("capacity:"+buf.capacity());
        
        //6. clear() : 清空缓冲区. 但是缓冲区中的数据依然存在，但是处于“被遗忘”状态
        buf.clear();
        
        System.out.println("-----------------clear()----------------");
        System.out.println("position:"+buf.position());
        System.out.println("limit:"+buf.limit());
        System.out.println("capacity:"+buf.capacity());
        
        System.out.println((char)buf.get());
        
    }
	
/**
 * 一、通道（Channel）：用于源节点与目标节点的连接。在 Java NIO 中负责缓冲区中数据的传输。Channel 本身不存储数据，因此需要配合缓冲区进行传输。
 * 
 * 二、通道的主要实现类
 *     java.nio.channels.Channel 接口：
 *         |--FileChannel
 *         |--SocketChannel
 *         |--ServerSocketChannel
 *         |--DatagramChannel
 * 
 * 三、获取通道
 * 1. Java 针对支持通道的类提供了 getChannel() 方法
 *         本地 IO：
 *         FileInputStream/FileOutputStream
 *         RandomAccessFile
 * 
 *         网络IO：
 *         Socket
 *         ServerSocket
 *         DatagramSocket
 *         
 * 2. 在 JDK 1.7 中的 NIO.2 针对各个通道提供了静态方法 open()
 * 3. 在 JDK 1.7 中的 NIO.2 的 Files 工具类的 newByteChannel()
 * 
 * 四、通道之间的数据传输
 * transferFrom()
 * transferTo()
 * 
 * 五、分散(Scatter)与聚集(Gather)
 * 分散读取（Scattering Reads）：将通道中的数据分散到多个缓冲区中
 * 聚集写入（Gathering Writes）：将多个缓冲区中的数据聚集到通道中
 * 
 * 六、字符集：Charset
 * 编码：字符串 -> 字节数组
 * 解码：字节数组  -> 字符串
 * 
 **/
	
	//利用通道完成文件的复制（非直接缓冲区） 耗费时间为：238Millis Seconds
	public static void test4(){//10874-10953    	
        long start = System.currentTimeMillis();
        
        FileInputStream fis = null;
        FileOutputStream fos = null;
        //①获取通道
        FileChannel inChannel = null;
        FileChannel outChannel = null;
        try {
            fis = new FileInputStream(file1);
            fos = new FileOutputStream(file2);
            
            inChannel = fis.getChannel();
            outChannel = fos.getChannel();
            
            //②分配指定大小的缓冲区
            ByteBuffer buf = ByteBuffer.allocate(1024);
            
            //③将通道中的数据存入缓冲区中
            while(inChannel.read(buf) != -1){
                buf.flip(); //切换读取数据的模式==>buf.position=0
                //④将缓冲区中的数据写入通道中
                outChannel.write(buf);
                buf.clear(); //清空缓冲区
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if(outChannel != null){
                try {
                    outChannel.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            
            if(inChannel != null){
                try {
                    inChannel.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            
            if(fos != null){
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            
            if(fis != null){
                try {
                    fis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        
        long end = System.currentTimeMillis();
        System.out.println("耗费时间为：" + (end - start)+"Millis Seconds");
        
    }

	//使用直接缓冲区完成文件的复制(内存映射文件) 耗费时间为：47 Millis Seconds.   
    public static void test5() throws IOException{//2127-1902-1777
        long start = System.currentTimeMillis();
        
        String fn1=URLDecoder.decode(file1.substring(1),"utf8");
        String fn2=URLDecoder.decode(file2.substring(1),"utf8");
        FileChannel inChannel = FileChannel.open(Paths.get(fn1), StandardOpenOption.READ);
        FileChannel outChannel = FileChannel.open(Paths.get(fn2), StandardOpenOption.WRITE, StandardOpenOption.READ, StandardOpenOption.CREATE);
        //内存映射文件
        MappedByteBuffer inMappedBuf = inChannel.map(MapMode.READ_ONLY, 0, inChannel.size());
        MappedByteBuffer outMappedBuf = outChannel.map(MapMode.READ_WRITE, 0, inChannel.size());
        
        //直接对缓冲区进行数据的读写操作
        byte[] dst = new byte[inMappedBuf.limit()];
        inMappedBuf.get(dst);
        outMappedBuf.put(dst);
        
        inChannel.close();
        outChannel.close();
        
        long end = System.currentTimeMillis();
        System.out.println("耗费时间为：" + (end - start)+" Millis Seconds.");
    }

    //通道之间的数据传输(直接缓冲区) 耗费时间为：15 Millis Seconds.
    public static void test6() throws IOException{
        //FileChannel inChannel = FileChannel.open(Paths.get("d:/1.mkv"), StandardOpenOption.READ);
        //FileChannel outChannel = FileChannel.open(Paths.get("d:/2.mkv"), StandardOpenOption.WRITE, StandardOpenOption.READ, StandardOpenOption.CREATE);
        
    	long start = System.currentTimeMillis();
        
        String fn1=URLDecoder.decode(file1.substring(1),"utf8");
        String fn2=URLDecoder.decode(file2.substring(1),"utf8");
        FileChannel inChannel = FileChannel.open(Paths.get(fn1), StandardOpenOption.READ);
        FileChannel outChannel = FileChannel.open(Paths.get(fn2), StandardOpenOption.WRITE, StandardOpenOption.READ, StandardOpenOption.CREATE);
        
        outChannel.transferFrom(inChannel, 0, inChannel.size());
        
        inChannel.close();
        outChannel.close();
        long end = System.currentTimeMillis();
        System.out.println("耗费时间为：" + (end - start)+" Millis Seconds.");
    }
    
    //分散和聚集    
    public static void test7() throws IOException{
        RandomAccessFile raf1 = new RandomAccessFile("alice30.txt", "rw");        
        //1. 获取通道
        FileChannel channel1 = raf1.getChannel();        
        //2. 分配指定大小的缓冲区
        ByteBuffer buf1 = ByteBuffer.allocate(100);
        ByteBuffer buf2 = ByteBuffer.allocate(1024);        
        //3. 分散读取
        ByteBuffer[] bufs = {buf1, buf2};
        channel1.read(bufs);        
        for (ByteBuffer byteBuffer : bufs) {
            byteBuffer.flip();
        }
        raf1.close();
        System.out.println(new String(bufs[0].array(), 0, bufs[0].limit()));
        System.out.println("-----------------");
        System.out.println(new String(bufs[1].array(), 0, bufs[1].limit()));        
        //4. 聚集写入
        RandomAccessFile raf2 = new RandomAccessFile("2.txt", "rw");
        FileChannel channel2 = raf2.getChannel();
        
        channel2.write(bufs);
        raf2.close();
    }

    public static void test8(){
        Map<String, Charset> map = Charset.availableCharsets();        
        Set<Entry<String, Charset>> set = map.entrySet();        
        for (Entry<String, Charset> entry : set) {
            System.out.println(entry.getKey() + "=" + entry.getValue());
        }
    }
    
    public static void test9() throws IOException{
        Charset cs1 = Charset.forName("GBK");        
        //获取编码器
        CharsetEncoder ce = cs1.newEncoder();        
        //获取解码器
        CharsetDecoder cd = cs1.newDecoder();        
        CharBuffer cBuf = CharBuffer.allocate(1024);
        cBuf.put("ABCDEFGHIJKL");
        cBuf.flip();        
        //编码
        ByteBuffer bBuf = ce.encode(cBuf);        
        for (int i = 0; i < 12; i++) {
            System.out.println(bBuf.get());
        }
        
        //解码
        bBuf.flip();
        CharBuffer cBuf2 = cd.decode(bBuf);
        System.out.println(cBuf2.toString());        
        System.out.println("------------------------------------------------------");
        
        Charset cs2 = Charset.forName("GBK");
        bBuf.flip();
        CharBuffer cBuf3 = cs2.decode(bBuf);
        System.out.println(cBuf3.toString());
    }

    //将数据从源通道传输到另一个通道
    public static void transferfrom() throws IOException{
    	RandomAccessFile fromFile=new RandomAccessFile("fromfile.txt","rw");
    	FileChannel fromChannel=fromFile.getChannel();
    	RandomAccessFile toFile=new RandomAccessFile("tofile.txt","rw");
    	FileChannel toChannel=toFile.getChannel();
    	long position=0L;
    	long count=fromChannel.size();    	
    	toChannel.transferFrom(fromChannel,position,count);
    	fromFile.close();
    	toFile.close();
    }
    
    //将数据从源通道传输到另一个通道
    @SuppressWarnings("resource")
	public static void transferto() throws IOException{
    	RandomAccessFile fromFile=new RandomAccessFile("fromfile.txt","rw");
    	FileChannel fromChannel=fromFile.getChannel();
    	RandomAccessFile toFile=new RandomAccessFile("tofile.txt","rw");
    	FileChannel toChannel=toFile.getChannel();
    	long position=0L;
    	long count=fromChannel.size();    	
    	fromChannel.transferTo(position,count,toChannel);
    }
    
/**
 * 一、使用 NIO 完成网络通信的三个核心： * 
 * 1. 通道（Channel）：负责连接 *         
 *        java.nio.channels.Channel 接口：
 *             |--SelectableChannel
 *                 |--SocketChannel
 *                 |--ServerSocketChannel
 *                 |--DatagramChannel
 * 
 *                 |--Pipe.SinkChannel
 *                 |--Pipe.SourceChannel
 * 
 * 2. 缓冲区（Buffer）：负责数据的存取 * 
 * 3. 选择器（Selector）：是 SelectableChannel 的多路复用器。用于监控 SelectableChannel 的 IO 状况 * 
 * */
	//客户端:不采用选择器，阻塞式NIO客户端
    public void client() throws IOException{
        //1. 获取通道
        SocketChannel sChannel = SocketChannel.open(new InetSocketAddress("127.0.0.1", 9898));        
        FileChannel inChannel = FileChannel.open(Paths.get("1.jpg"), StandardOpenOption.READ);        
        //2. 分配指定大小的缓冲区
        ByteBuffer buf = ByteBuffer.allocate(1024);        
        //3. 读取本地文件，并发送到服务端
        while(inChannel.read(buf) != -1){
            buf.flip();
            sChannel.write(buf);
            buf.clear();
        }        
        //4. 关闭通道
        inChannel.close();
        sChannel.close();
    }
	//服务端:不采用选择器，阻塞式NIO服务端
    public void server() throws IOException{
    	//1. 获取通道
        ServerSocketChannel ssChannel = ServerSocketChannel.open();        
        FileChannel outChannel = FileChannel.open(Paths.get("2.jpg"), StandardOpenOption.WRITE, StandardOpenOption.CREATE);
        //2. 绑定连接
        ssChannel.bind(new InetSocketAddress(9898));        
        //3. 获取客户端连接的通道
        SocketChannel sChannel = ssChannel.accept();        
        //4. 分配指定大小的缓冲区
        ByteBuffer buf = ByteBuffer.allocate(1024);        
        //5. 接收客户端的数据，并保存到本地
        while(sChannel.read(buf) != -1){
            buf.flip();
            outChannel.write(buf);
            buf.clear();
        }        
        //6. 关闭通道
        sChannel.close();
        outChannel.close();
        ssChannel.close();        
    }
    
    /**
     * 解决上面的方法，以前没有选择器的时候，对于阻塞情况，我们可以采用下面的方法：（发送完成，自动自己关闭告知已发送完成）
     * */
	//客户端
    public void client2() throws IOException{
        SocketChannel sChannel = SocketChannel.open(new InetSocketAddress("127.0.0.1", 9898));        
        FileChannel inChannel = FileChannel.open(Paths.get("1.jpg"), StandardOpenOption.READ);        
        ByteBuffer buf = ByteBuffer.allocate(1024);        
        while(inChannel.read(buf) != -1){
            buf.flip();
            sChannel.write(buf);
            buf.clear();
        }        
        sChannel.shutdownOutput();
        
        //接收服务端的反馈
        int len = 0;
        while((len = sChannel.read(buf)) != -1){
            buf.flip();
            System.out.println(new String(buf.array(), 0, len));
            buf.clear();
        }        
        inChannel.close();
        sChannel.close();
    }
    
    //服务端
    public void server2() throws IOException{
        ServerSocketChannel ssChannel = ServerSocketChannel.open();        
        FileChannel outChannel = FileChannel.open(Paths.get("2.jpg"), StandardOpenOption.WRITE, StandardOpenOption.CREATE);
        ssChannel.bind(new InetSocketAddress(9898));        
        SocketChannel sChannel = ssChannel.accept();        
        ByteBuffer buf = ByteBuffer.allocate(1024);        
        while(sChannel.read(buf) != -1){
            buf.flip();
            outChannel.write(buf);
            buf.clear();
        }        
        //发送反馈给客户端
        buf.put("服务端接收数据成功".getBytes());
        buf.flip();
        sChannel.write(buf);
        
        sChannel.close();
        outChannel.close();
        ssChannel.close();
    }

    /**
     * 选择器（Selector） 是 SelectableChannle 对象的多路复用器， Selector 可以同时监控多个 SelectableChannel 的 IO 状况，
     * 也就是说，利用 Selector可使一个单独的线程管理多个 Channel。 Selector 是非阻塞 IO 的核心。
     * */
	//客户端:采用选择器，非阻塞式NIO客户端
    public void client3() throws IOException{
        //1. 获取通道
        SocketChannel sChannel = SocketChannel.open(new InetSocketAddress("127.0.0.1", 9898));        
        //2. 切换非阻塞模式
        sChannel.configureBlocking(false);        
        //3. 分配指定大小的缓冲区
        ByteBuffer buf = ByteBuffer.allocate(1024);        
        //4. 发送数据给服务端
        Scanner scan = new Scanner(System.in);        
        while(scan.hasNext()){
            String str = scan.next();
            buf.put((new Date().toString() + "\n" + str).getBytes());
            buf.flip();
            sChannel.write(buf);
            buf.clear();
        }        
        //5. 关闭通道
        sChannel.close();
        scan.close();
    }
    
	//服务端:采用选择器，非阻塞式NIO服务端
    public void server3() throws IOException{
        //1. 获取通道
        ServerSocketChannel ssChannel = ServerSocketChannel.open();        
        //2. 切换非阻塞模式
        ssChannel.configureBlocking(false);        
        //3. 绑定连接
        ssChannel.bind(new InetSocketAddress(9898));        
        //4. 获取选择器
        Selector selector = Selector.open();        
        //5. 将通道注册到选择器上, 并且指定“监听接收事件”
        ssChannel.register(selector, SelectionKey.OP_ACCEPT);        
        //6. 轮询式的获取选择器上已经“准备就绪”的事件
        while(selector.select() > 0){            
            //7. 获取当前选择器中所有注册的“选择键(已就绪的监听事件)”
            Iterator<SelectionKey> it = selector.selectedKeys().iterator();            
            while(it.hasNext()){
                //8. 获取准备“就绪”的是事件
                SelectionKey sk = it.next();                
                //9. 判断具体是什么事件准备就绪
                if(sk.isAcceptable()){
                    //10. 若“接收就绪”，获取客户端连接
                    SocketChannel sChannel = ssChannel.accept();                    
                    //11. 切换非阻塞模式
                    sChannel.configureBlocking(false);                    
                    //12. 将该通道注册到选择器上
                    sChannel.register(selector, SelectionKey.OP_READ);
                }else if(sk.isReadable()){
                    //13. 获取当前选择器上“读就绪”状态的通道
                    SocketChannel sChannel = (SocketChannel) sk.channel();                    
                    //14. 读取数据
                    ByteBuffer buf = ByteBuffer.allocate(1024);                    
                    int len = 0;
                    while((len = sChannel.read(buf)) > 0 ){
                        buf.flip();
                        System.out.println(new String(buf.array(), 0, len));
                        buf.clear();
                    }
                }                
                //15. 取消选择键 SelectionKey
                it.remove();
            }
        }
    }
    
    /**
     * DatagramChannel:Java NIO中的DatagramChannel是一个能收发UDP包的通道。
     *  操作步骤：
     *  打开 DatagramChannel
     *  接收/发送数据
     * */
	public void send() throws IOException{
        DatagramChannel dc = DatagramChannel.open();        
        dc.configureBlocking(false);        
        ByteBuffer buf = ByteBuffer.allocate(1024);        
        Scanner scan = new Scanner(System.in);        
        while(scan.hasNext()){
            String str = scan.next();
            buf.put((new Date().toString() + ":\n" + str).getBytes());
            buf.flip();
            dc.send(buf, new InetSocketAddress("127.0.0.1", 9898));
            buf.clear();
        }        
        dc.close();
        scan.close();
    }
    
    public void receive() throws IOException{
        DatagramChannel dc = DatagramChannel.open();        
        dc.configureBlocking(false);        
        dc.bind(new InetSocketAddress(9898));        
        Selector selector = Selector.open();        
        dc.register(selector, SelectionKey.OP_READ);        
        while(selector.select() > 0){
            Iterator<SelectionKey> it = selector.selectedKeys().iterator();            
            while(it.hasNext()){
                SelectionKey sk = it.next();                
                if(sk.isReadable()){
                    ByteBuffer buf = ByteBuffer.allocate(1024);                    
                    dc.receive(buf);
                    buf.flip();
                    System.out.println(new String(buf.array(), 0, buf.limit()));
                    buf.clear();
                }
            }            
            it.remove();
        }
    }
    
	private static String file1=NIOTest.class.getResource("C2p1.mp4").getPath();
	private static String file2=NIOTest.class.getResource("C2p1_1.mp4").getPath();
}
