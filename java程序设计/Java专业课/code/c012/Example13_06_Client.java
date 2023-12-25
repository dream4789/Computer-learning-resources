import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.Date;
import java.util.Scanner;
import java.util.Set;

public class Example13_06_Client {
    static ByteBuffer sBuffer = ByteBuffer.allocate(1024);//创建发送数据缓冲区
    static ByteBuffer rBuffer = ByteBuffer.allocate(1024);//创建接收数据缓冲区
    InetSocketAddress Server;//服务器端socket地址对象
    static Selector selector;//选择器对象
    static SocketChannel client;//客户端通道对象
    static String receiveText;//接收字符串的内容
    static String sendText;//发送字符串的内容
    static int count = 0;//读取数据长度

    public Example13_06_Client(String serverIP,int port) {//
        Server = new InetSocketAddress(serverIP, port);//设置服务器socket地址对象
        init();
    }
    
    public void init() {
        try {
            SocketChannel socketChannel = SocketChannel.open();//创建一个Socket通道对象
            socketChannel.configureBlocking(false);//设置通道为非阻塞模式
            selector = Selector.open();//创建一个选择器对象
            socketChannel.register(selector, SelectionKey.OP_CONNECT);//注册通道到选择器，设置操作模式为连接操作
            socketChannel.connect(Server);//通道向服务器端发送连接请求
            while (true) {//轮询监听客户端上注册的操作事件
                selector.select();//选择准备就绪的通道
                Set<SelectionKey> selectionKeys = selector.selectedKeys();//获得选择器的已选择键集合
                for (final SelectionKey key : selectionKeys) {//遍历已选择键对该选择键通道进行相关处理
                    handle(key);//对该选择键通道进行处理
                }
                selectionKeys.clear();//清空已选择键集合
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args)  {
        	new Example13_06_Client("127.0.0.1",8989);
    }    
    void handle(SelectionKey selectionKey) throws IOException {//处理已选择键通道
          	if (selectionKey.isConnectable()) {//处理建立连接操作
              client = (SocketChannel)selectionKey.channel();//获取当前键对应的通道
            if (client.isConnectionPending()) {//如果客户端与服务器端正在连接
                client.finishConnect();//完成相互连接
                System.out.println("connect success !");
                sBuffer.clear();//准备写缓冲区
                sBuffer.put((new Date() + " connected!").getBytes());//向缓冲区写数据
                sBuffer.flip();//准备读缓冲区
                client.write(sBuffer);//读取缓冲区数据至服务器  
                new Thread() {//创建写线程，向服务器端发送聊天内容
                    public void run() {
                        while (true) {
                            try {
                                sBuffer.clear();
                                Scanner cin =new Scanner(System.in);
                                sendText = cin.nextLine();
                                sBuffer.put(sendText.getBytes("utf-8"));//将聊天内容写入缓冲区
                                sBuffer.flip();
                                try{
                                client.write(sBuffer);//将缓冲区内容发送给服务器端
                                }catch (java.nio.channels.ClosedChannelException e1){
                                	System.out.println("与服务器远程连接中断!");
                                	client.close();
                                	System.exit(0);
                                }
                            }catch (IOException e) {
                                e.printStackTrace();
                                break;
                            }
                        }
                    };
                }.start();
            }
            client.register(selector, SelectionKey.OP_READ);//注册通道并设置操作模式为读操作
        }
        else if (selectionKey.isReadable()) {//处理读操作
            try{
        	client = (SocketChannel)selectionKey.channel();//获取当前待读操作的通道
            rBuffer.clear();
            count = client.read(rBuffer);//读取通道内容到缓冲区
            if (count > 0) {//如果有内容
                receiveText = new String(rBuffer.array(), 0, count);
                System.out.println(receiveText);
               }
            }catch(IOException e){
            	client.close();
            }
        }
    }
}
