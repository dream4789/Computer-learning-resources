import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Set;

public class Example8_09 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HashMap<String,String> tel_list = new HashMap();
		tel_list.put("wang li", "135678912");
		tel_list.put("li ying", "159234571");
		tel_list.put("zhang san", "187654321");
		tel_list.put("li si","188345678");
		Set<Entry<String, String>> list =tel_list.entrySet();//����ӳ�伯�ϵ�Set��ͼ
		System.out.println("Telephone list:");
		for (Entry t:list){//�����������-ֵ������
			System.out.printf("name: %-10s; tel_number: %s\n",t.getKey(),t.getValue());
		}
	}
}
