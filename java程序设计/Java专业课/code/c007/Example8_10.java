import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Set;

public class import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class Example8_10 {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		ArrayList<String> list = new ArrayList<String>();
		System.out.println("������10���ַ���:");
		//��ȡ10�����Ȳ�һ���ַ���
		for (int i=0;i<10;i++){
			list.add(scanner.next());
		}
		ArrayList list1 = new ArrayList(list);
		//ͨ��ѭ���������飬ɾ��ż�����ȵ��ַ���
		int i=0;
		while (i<list.size()){
			if (list.get(i).length()%2 == 0)
				list.remove(i);
			else
				i++;
		}
		System.out.println(list);
		//ʹ�õ�����ʵ����ͬ����
		Iterator iter = list1.iterator(); 
		while (iter.hasNext()){
			String s = (String)iter.next();
			if (s.length()%2==0)
				iter.remove();
		}
		System.out.println(list1);
	}
}
 {

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
