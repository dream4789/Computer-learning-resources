import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class Example13_06_Server {
    int port;
    Charset cs = Charset.forName("utf-8");//设置缓冲区编码
    static ByteBuffer sBuffer = ByteBuffer.allocate(1024);//创建接收数据缓冲区
    static ByteBuffer rBuffer = ByteBuffer.allocate(1024);//创建发送数据缓冲区
    Map<String, SocketChannel> clientsMap = new HashMap<String, SocketChannel>();//映射客户端通道
    static Selector selector;
    static String address;
    
    public  Example13_06_Server(int port) {
        this.port = port;
        try {
            init();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    void init() throws IOException {
        ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();//创建服务器端监听连接通道
        serverSocketChannel.configureBlocking(false);//设置监听连接通道为非阻塞模式
        ServerSocket serverSocket = serverSocketChannel.socket();//获取服务器端socket对象
        serverSocket.bind(new InetSocketAddress(port));//绑定监听连接通道到指定端口
        selector = Selector.open();//创建选择器
        serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);//注册通道并设置操作模式为可连接模式
        System.out.println("server start on port:" + port);
    }

    void listen() {//轮询监听注册通道的操作
        while (true) {
            try {
                selector.select();//选择准备就绪的通道
                int i=0;
                Set<SelectionKey> selectionKeys = selector.selectedKeys();//获得选择器的已选择键集合
                for (SelectionKey key : selectionKeys) {//遍历已选择键对该选择键通道进行相关处理
                     	handle(key);//对该选择键通道进行处理
                }
                selectionKeys.clear();//清空已选择键集合
            }
            catch (Exception e) {
                System.out.println("interrupt");
                e.printStackTrace();
                
                break;
            }
        }
    }
      void handle(SelectionKey selectionKey) throws IOException {
        ServerSocketChannel server = null;
        SocketChannel client = null;
        String receiveText = null;
        int count = 0;
        
        if (selectionKey.isAcceptable()) {//处理可连接操作
            server = (ServerSocketChannel)selectionKey.channel();
            client = server.accept();//接受客户端的连接，获取连接的通道
            client.configureBlocking(false);
            address = "[" + client.getRemoteAddress().toString().substring(1)  + "]";
            clientsMap.put(address, client);
            client.register(selector, SelectionKey.OP_READ);
        }
        else if (selectionKey.isReadable()) {//处理读操作
        	try{
        	client = (SocketChannel)selectionKey.channel();//获取当前待读操作的通道
            rBuffer.clear();
            count = client.read(rBuffer);//读取通道内容到缓冲区
            if (count > 0) {
            	address = "[" + client.getRemoteAddress().toString().substring(1)  + "]";
                rBuffer.flip();
                receiveText = String.valueOf(cs.decode(rBuffer).array());
                System.out.println(address+":"+ receiveText);
                 dispatch(client, receiveText);
             }
            }catch(IOException e){
            	System.out.println(client.getRemoteAddress().toString()+" interrupt"); 
            	clientsMap.remove(address);
            	client.close();
            	selectionKey.cancel();
             }
        }
       
    }
  void dispatch(SocketChannel client, String info) throws IOException {//发送内容到其他客户端
      try{ 
    	  address = "[" + client.getRemoteAddress().toString().substring(1)  + "]";
    	  if (!clientsMap.isEmpty()) {//遍历客户端通道集合
            for (Map.Entry<String, SocketChannel> entry : clientsMap.entrySet()) {
                SocketChannel temp = entry.getValue();
                if (!client.equals(temp)) {//如果不是当前通道，则转发内容到该通道
                	sBuffer.clear();
                    sBuffer.put((address + ":" + info).getBytes());
                    sBuffer.flip();
                    temp.write(sBuffer);//输出到通道
                }
            }
        }
      }catch(IOException e){
    	  System.out.println("分发数据异常");
      }
    }
    
    public static void main(String[] args) throws IOException {
        Example13_06_Server server = new Example13_06_Server(8989);
        server.listen();
    }
}
