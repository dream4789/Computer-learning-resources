import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.Set;

public class Example11_15 {

	public static void main(String[] args) throws Exception{
		
		RandomAccessFile file = new RandomAccessFile("d:\\abc.txt", "r");//建立文件对象
		FileChannel channel = file.getChannel();//建立文件通道
		ByteBuffer buf = ByteBuffer.allocate(128);//设置字节缓冲区
		Map<String,Integer> map=new HashMap<String,Integer>();//保存单词和出现次数
				
		while(channel.read(buf)!=-1){//读取文件内容并显示
			buf.flip();//准备缓冲区读取
			String reader_string =new String(buf.array()).trim();
			Scanner scanner = new Scanner(reader_string);
			scanner.useDelimiter("[ \r\n]+");//设置分隔符
			while (scanner.hasNext()){
				String word = scanner.next();
				
				if(map.containsKey(word)){ //HashMap不允许重复的key，所以利用这个特性，去统计单词的个数  
		            int count=map.get(word);  
		            map.put(word, count+1); //如果HashMap已有这个单词，则设置它的数量加1  
		        }  
		        else  
		            map.put(word, 1); //如果没有这个单词，则新填入，数量为1  
		    }
		}
		int count=0;
		Set<Entry<String, Integer>> list =map.entrySet();//返回映射集合的Set视图
		for (Entry t:list){
			if(t.getValue()==Integer.valueOf(1))//如果单词出现的次数为1，则进行累加
				count++;
		}
		System.out.println("非重复单词数量为:"+count);
	}
}
