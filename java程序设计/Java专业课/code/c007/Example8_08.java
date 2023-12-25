import java.util.HashMap;
public class Example8_08 {
	public static void main(String[] args) {
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
String number = tel_list.get("zhang san");//查询zhang san的电话号
		System.out.println("zhang san'number:"+number);
	}
}

