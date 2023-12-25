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
		System.out.println("请输入10个字符串:");
		//读取10个长度不一的字符串
		for (int i=0;i<10;i++){
			list.add(scanner.next());
		}
		ArrayList list1 = new ArrayList(list);
		//通过循环遍历数组，删除偶数长度的字符串
		int i=0;
		while (i<list.size()){
			if (list.get(i).length()%2 == 0)
				list.remove(i);
			else
				i++;
		}
		System.out.println(list);
		//使用迭代器实现相同功能
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
		Set<Entry<String, String>> list =tel_list.entrySet();//返回映射集合的Set视图
		System.out.println("Telephone list:");
		for (Entry t:list){//遍历输出各键-值对内容
			System.out.printf("name: %-10s; tel_number: %s\n",t.getKey(),t.getValue());
		}
	}
}
