import java.net.InetAddress; 
import java.util.ArrayList; 
import java.util.GregorianCalendar; 
import java.util.List; 
import jpcap.JpcapCaptor; 
import jpcap.JpcapSender; 
import jpcap.NetworkInterface; 
import jpcap.packet.EthernetPacket; 
import jpcap.packet.ICMPPacket; 
import jpcap.packet.IPPacket; 

public class Example13_07 { 

 private NetworkInterface[] devices = JpcapCaptor.getDeviceList();//��ñ��������豸
 private JpcapSender sender; 
 private JpcapCaptor jpcap; 
 private ICMPPacket icmpPacket; 
 private List<String> listResult = new ArrayList<String>(); 
 private long delay;
 
 public void ping(String ip) { 
  try { 
   jpcap = JpcapCaptor.openDevice(devices[0], 200, false, 20); //deviceΪ�����豸�ӿڣ���ͬ�Ļ����������ܲ�ͬ
   sender = jpcap.getJpcapSenderInstance(); 
   jpcap.setFilter("icmp", true);// ���ù�������ֻ����ICMP���� 
   icmpPacket = new ICMPPacket();//����icmp������ 
   icmpPacket.type = ICMPPacket.ICMP_ECHO; // ���ͻ��������� 
   icmpPacket.setIPv4Parameter(0, false, false, false, 0, false, 
		     false, false, 0, 1010101, 100, IPPacket.IPPROTO_ICMP, InetAddress.getLocalHost(),
		      InetAddress.getByName(ip));//����icmp����ͷ��ip����ΪԶ��������ַIP
   icmpPacket.data = "abcdefghijklmnopqrstuvwxyzabcdef".getBytes(); //icmp�����ݣ������32bytes���� 
   EthernetPacket ethernetPacket = new EthernetPacket(); 
   ethernetPacket.frametype = EthernetPacket.ETHERTYPE_IP; 
   ethernetPacket.src_mac = devices[0].mac_address; //�����豸mac��ַ
   ethernetPacket.dst_mac = new byte[] { (byte) 0x00, (byte) 0x1a, 
     (byte) 0xa9, (byte) 0x08, (byte) 0xa6, (byte) 0x4b }; //��������mac��ַ
   icmpPacket.datalink = ethernetPacket; 
   listResult.add("Pinging " + icmpPacket.dst_ip + " with " 
     + icmpPacket.data.length + " bytes of data: "); 
   for (int i = 0; i < 5; i++) { //����5��ICMP�����
    icmpPacket.sec = 0; 
    icmpPacket.usec = new GregorianCalendar().getTimeInMillis();// ��¼����ʱ�� 
    icmpPacket.seq = (short) (1000 + i); //����icmp����Ψһ��ʶ
    icmpPacket.id = (short) (999 + i); 
    sender.sendPacket(icmpPacket); //����icmp��
    getIcmpPacket(jpcap);//����icmp��
    try { 
     Thread.sleep(1000); 
    } catch (Exception e) { 
     e.printStackTrace(); 
    } 
   }
   System.out.println("ƽ����ʱ��"+(int)(delay/5));
  } catch (Exception e) { 
   e.printStackTrace(); 
  } 
 } 
 
 public void getIcmpPacket(JpcapCaptor jpcapCaptor) { //������Ӧ������������ʱ
  try { 
   while (true) { 
    long tmp = 0;
    long seconds=0;
    String tmpStr = null; 
    ICMPPacket rp; 

    rp = (ICMPPacket) jpcapCaptor.getPacket(); 

    if ((rp != null) && (rp.seq - rp.id == 1) 
      && (rp.type == ICMPPacket.ICMP_ECHOREPLY)) { // ����ICMP��Ӧ����
        	seconds=new GregorianCalendar().getTimeInMillis();//���㷵��ʱ��
    	tmp=seconds-icmpPacket.usec;//������Ӧʱ��
     if (tmp <= 0) 
      tmpStr = " < 1 ms "; 
     else 
      tmpStr = "= " + tmp + " ms  "; 
     delay+=tmp; //��ϼ�ʱ��
     System.out.println("Reply from " 
       + rp.src_ip.getHostAddress() + ": bytes = " 
       + rp.data.length + " time " + tmpStr + "TTL = " 
       + rp.hop_limit); 

     listResult.add("Reply from " + rp.src_ip.getHostAddress() 
       + ": bytes = " + rp.data.length + " time " + tmpStr 
       + "TTL = " + rp.hop_limit); 
     break;
    } 
   } 
  } catch (Exception e) { 
   e.printStackTrace(); 
  } 
} 

 public static void main(String[] args) {
	 Example13_07 in=new Example13_07();
	 in.ping("www.google.com");
	 in.ping("www.sohu.com");
	 } 
}
