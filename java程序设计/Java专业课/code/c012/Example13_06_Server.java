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
    Charset cs = Charset.forName("utf-8");//���û���������
    static ByteBuffer sBuffer = ByteBuffer.allocate(1024);//�����������ݻ�����
    static ByteBuffer rBuffer = ByteBuffer.allocate(1024);//�����������ݻ�����
    Map<String, SocketChannel> clientsMap = new HashMap<String, SocketChannel>();//ӳ��ͻ���ͨ��
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
        ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();//�����������˼�������ͨ��
        serverSocketChannel.configureBlocking(false);//���ü�������ͨ��Ϊ������ģʽ
        ServerSocket serverSocket = serverSocketChannel.socket();//��ȡ��������socket����
        serverSocket.bind(new InetSocketAddress(port));//�󶨼�������ͨ����ָ���˿�
        selector = Selector.open();//����ѡ����
        serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);//ע��ͨ�������ò���ģʽΪ������ģʽ
        System.out.println("server start on port:" + port);
    }

    void listen() {//��ѯ����ע��ͨ���Ĳ���
        while (true) {
            try {
                selector.select();//ѡ��׼��������ͨ��
                int i=0;
                Set<SelectionKey> selectionKeys = selector.selectedKeys();//���ѡ��������ѡ�������
                for (SelectionKey key : selectionKeys) {//������ѡ����Ը�ѡ���ͨ��������ش���
                     	handle(key);//�Ը�ѡ���ͨ�����д���
                }
                selectionKeys.clear();//�����ѡ�������
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
        
        if (selectionKey.isAcceptable()) {//��������Ӳ���
            server = (ServerSocketChannel)selectionKey.channel();
            client = server.accept();//���ܿͻ��˵����ӣ���ȡ���ӵ�ͨ��
            client.configureBlocking(false);
            address = "[" + client.getRemoteAddress().toString().substring(1)  + "]";
            clientsMap.put(address, client);
            client.register(selector, SelectionKey.OP_READ);
        }
        else if (selectionKey.isReadable()) {//���������
        	try{
        	client = (SocketChannel)selectionKey.channel();//��ȡ��ǰ����������ͨ��
            rBuffer.clear();
            count = client.read(rBuffer);//��ȡͨ�����ݵ�������
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
  void dispatch(SocketChannel client, String info) throws IOException {//�������ݵ������ͻ���
      try{ 
    	  address = "[" + client.getRemoteAddress().toString().substring(1)  + "]";
    	  if (!clientsMap.isEmpty()) {//�����ͻ���ͨ������
            for (Map.Entry<String, SocketChannel> entry : clientsMap.entrySet()) {
                SocketChannel temp = entry.getValue();
                if (!client.equals(temp)) {//������ǵ�ǰͨ������ת�����ݵ���ͨ��
                	sBuffer.clear();
                    sBuffer.put((address + ":" + info).getBytes());
                    sBuffer.flip();
                    temp.write(sBuffer);//�����ͨ��
                }
            }
        }
      }catch(IOException e){
    	  System.out.println("�ַ������쳣");
      }
    }
    
    public static void main(String[] args) throws IOException {
        Example13_06_Server server = new Example13_06_Server(8989);
        server.listen();
    }
}
