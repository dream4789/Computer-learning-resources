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
		
		RandomAccessFile file = new RandomAccessFile("d:\\abc.txt", "r");//�����ļ�����
		FileChannel channel = file.getChannel();//�����ļ�ͨ��
		ByteBuffer buf = ByteBuffer.allocate(128);//�����ֽڻ�����
		Map<String,Integer> map=new HashMap<String,Integer>();//���浥�ʺͳ��ִ���
				
		while(channel.read(buf)!=-1){//��ȡ�ļ����ݲ���ʾ
			buf.flip();//׼����������ȡ
			String reader_string =new String(buf.array()).trim();
			Scanner scanner = new Scanner(reader_string);
			scanner.useDelimiter("[ \r\n]+");//���÷ָ���
			while (scanner.hasNext()){
				String word = scanner.next();
				
				if(map.containsKey(word)){ //HashMap�������ظ���key����������������ԣ�ȥͳ�Ƶ��ʵĸ���  
		            int count=map.get(word);  
		            map.put(word, count+1); //���HashMap����������ʣ�����������������1  
		        }  
		        else  
		            map.put(word, 1); //���û��������ʣ��������룬����Ϊ1  
		    }
		}
		int count=0;
		Set<Entry<String, Integer>> list =map.entrySet();//����ӳ�伯�ϵ�Set��ͼ
		for (Entry t:list){
			if(t.getValue()==Integer.valueOf(1))//������ʳ��ֵĴ���Ϊ1��������ۼ�
				count++;
		}
		System.out.println("���ظ���������Ϊ:"+count);
	}
}
