import java.util.*;
import java.util.stream.Collectors;

public class Example8_12 {

	public static void main(String[] args) {
		//创建一个字符串集合
		List<String> str =Arrays.asList("Hello","Mr","zhang","How","are","you","Today");
		//调用filter()方法过滤掉长度小于4的字符串，调用toUpper()方法进行字符串大写处理
		List<String> result =toUpper(filter(str));
		System.out.println("一般方法运行结果：");
		for (String s:result){//遍历输出处理好的字符串
			System.out.println(s);
		}
		System.out.println("使用Lambda表达式运行结果：");
		//利用Lambda表达式，完成相关处理并输出结果
	str.stream().filter(s->s.length()>=4).map(m->m.toUpperCase()).forEach(System.out::println);
	}
public static List<String> filter(List<String> str){//过滤方法，返回长度大于等于4的字符串集合
		List<String> list=new ArrayList<String>();
		for(String s:str){
			if (s.length()>=4){
				list.add(s);
			}
		}
		return list;
	}
public static List<String> toUpper(List<String> str){//字符串处理方法，将集合中所有字符串转换成大写字符
		ArrayList<String> ulist=new ArrayList<String>();
		for(String s :str){
			ulist.add(s.toUpperCase());
		}
		return ulist;
	}
}
