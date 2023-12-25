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
    static ByteBuffer sBuffer = ByteBuffer.allocate(1024);//�����������ݻ�����
    static ByteBuffer rBuffer = ByteBuffer.allocate(1024);//�����������ݻ�����
    InetSocketAddress Server;//��������socket��ַ����
    static Selector selector;//ѡ��������
    static SocketChannel client;//�ͻ���ͨ������
    static String receiveText;//�����ַ���������
    static String sendText;//�����ַ���������
    static int count = 0;//��ȡ���ݳ���

    public Example13_06_Client(String serverIP,int port) {//
        Server = new InetSocketAddress(serverIP, port);//���÷�����socket��ַ����
        init();
    }
    
    public void init() {
        try {
            SocketChannel socketChannel = SocketChannel.open();//����һ��Socketͨ������
            socketChannel.configureBlocking(false);//����ͨ��Ϊ������ģʽ
            selector = Selector.open();//����һ��ѡ��������
            socketChannel.register(selector, SelectionKey.OP_CONNECT);//ע��ͨ����ѡ���������ò���ģʽΪ���Ӳ���
            socketChannel.connect(Server);//ͨ����������˷�����������
            while (true) {//��ѯ�����ͻ�����ע��Ĳ����¼�
                selector.select();//ѡ��׼��������ͨ��
                Set<SelectionKey> selectionKeys = selector.selectedKeys();//���ѡ��������ѡ�������
                for (final SelectionKey key : selectionKeys) {//������ѡ����Ը�ѡ���ͨ��������ش���
                    handle(key);//�Ը�ѡ���ͨ�����д���
                }
                selectionKeys.clear();//�����ѡ�������
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args)  {
        	new Example13_06_Client("127.0.0.1",8989);
    }    
    void handle(SelectionKey selectionKey) throws IOException {//������ѡ���ͨ��
          	if (selectionKey.isConnectable()) {//���������Ӳ���
              client = (SocketChannel)selectionKey.channel();//��ȡ��ǰ����Ӧ��ͨ��
            if (client.isConnectionPending()) {//����ͻ��������������������
                client.finishConnect();//����໥����
                System.out.println("connect success !");
                sBuffer.clear();//׼��д������
                sBuffer.put((new Date() + " connected!").getBytes());//�򻺳���д����
                sBuffer.flip();//׼����������
                client.write(sBuffer);//��ȡ������������������  
                new Thread() {//����д�̣߳���������˷�����������
                    public void run() {
                        while (true) {
                            try {
                                sBuffer.clear();
                                Scanner cin =new Scanner(System.in);
                                sendText = cin.nextLine();
                                sBuffer.put(sendText.getBytes("utf-8"));//����������д�뻺����
                                sBuffer.flip();
                                try{
                                client.write(sBuffer);//�����������ݷ��͸���������
                                }catch (java.nio.channels.ClosedChannelException e1){
                                	System.out.println("�������Զ�������ж�!");
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
            client.register(selector, SelectionKey.OP_READ);//ע��ͨ�������ò���ģʽΪ������
        }
        else if (selectionKey.isReadable()) {//���������
            try{
        	client = (SocketChannel)selectionKey.channel();//��ȡ��ǰ����������ͨ��
            rBuffer.clear();
            count = client.read(rBuffer);//��ȡͨ�����ݵ�������
            if (count > 0) {//���������
                receiveText = new String(rBuffer.array(), 0, count);
                System.out.println(receiveText);
               }
            }catch(IOException e){
            	client.close();
            }
        }
    }
}
