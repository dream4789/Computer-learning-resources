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

 private NetworkInterface[] devices = JpcapCaptor.getDeviceList();//获得本地网络设备
 private JpcapSender sender; 
 private JpcapCaptor jpcap; 
 private ICMPPacket icmpPacket; 
 private List<String> listResult = new ArrayList<String>(); 
 private long delay;
 
 public void ping(String ip) { 
  try { 
   jpcap = JpcapCaptor.openDevice(devices[0], 200, false, 20); //device为网络设备接口，不同的机器索引可能不同
   sender = jpcap.getJpcapSenderInstance(); 
   jpcap.setFilter("icmp", true);// 设置过滤器，只接收ICMP报文 
   icmpPacket = new ICMPPacket();//创建icmp包对象 
   icmpPacket.type = ICMPPacket.ICMP_ECHO; // 发送回显请求报文 
   icmpPacket.setIPv4Parameter(0, false, false, false, 0, false, 
		     false, false, 0, 1010101, 100, IPPacket.IPPROTO_ICMP, InetAddress.getLocalHost(),
		      InetAddress.getByName(ip));//设置icmp报文头，ip参数为远程主机地址IP
   icmpPacket.data = "abcdefghijklmnopqrstuvwxyzabcdef".getBytes(); //icmp包内容，随意的32bytes数据 
   EthernetPacket ethernetPacket = new EthernetPacket(); 
   ethernetPacket.frametype = EthernetPacket.ETHERTYPE_IP; 
   ethernetPacket.src_mac = devices[0].mac_address; //本地设备mac地址
   ethernetPacket.dst_mac = new byte[] { (byte) 0x00, (byte) 0x1a, 
     (byte) 0xa9, (byte) 0x08, (byte) 0xa6, (byte) 0x4b }; //本地网关mac地址
   icmpPacket.datalink = ethernetPacket; 
   listResult.add("Pinging " + icmpPacket.dst_ip + " with " 
     + icmpPacket.data.length + " bytes of data: "); 
   for (int i = 0; i < 5; i++) { //发送5个ICMP请求包
    icmpPacket.sec = 0; 
    icmpPacket.usec = new GregorianCalendar().getTimeInMillis();// 记录发送时间 
    icmpPacket.seq = (short) (1000 + i); //设置icmp包的唯一标识
    icmpPacket.id = (short) (999 + i); 
    sender.sendPacket(icmpPacket); //发送icmp包
    getIcmpPacket(jpcap);//接收icmp包
    try { 
     Thread.sleep(1000); 
    } catch (Exception e) { 
     e.printStackTrace(); 
    } 
   }
   System.out.println("平均延时："+(int)(delay/5));
  } catch (Exception e) { 
   e.printStackTrace(); 
  } 
 } 
 
 public void getIcmpPacket(JpcapCaptor jpcapCaptor) { //接收响应包，并计算延时
  try { 
   while (true) { 
    long tmp = 0;
    long seconds=0;
    String tmpStr = null; 
    ICMPPacket rp; 

    rp = (ICMPPacket) jpcapCaptor.getPacket(); 

    if ((rp != null) && (rp.seq - rp.id == 1) 
      && (rp.type == ICMPPacket.ICMP_ECHOREPLY)) { // 捕获ICMP回应报文
        	seconds=new GregorianCalendar().getTimeInMillis();//计算返回时间
    	tmp=seconds-icmpPacket.usec;//计算响应时间
     if (tmp <= 0) 
      tmpStr = " < 1 ms "; 
     else 
      tmpStr = "= " + tmp + " ms  "; 
     delay+=tmp; //求合计时间
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
