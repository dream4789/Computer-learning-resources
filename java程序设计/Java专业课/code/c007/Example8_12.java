import java.util.*;
import java.util.stream.Collectors;

public class Example8_12 {

	public static void main(String[] args) {
		//����һ���ַ�������
		List<String> str =Arrays.asList("Hello","Mr","zhang","How","are","you","Today");
		//����filter()�������˵�����С��4���ַ���������toUpper()���������ַ�����д����
		List<String> result =toUpper(filter(str));
		System.out.println("һ�㷽�����н����");
		for (String s:result){//�����������õ��ַ���
			System.out.println(s);
		}
		System.out.println("ʹ��Lambda���ʽ���н����");
		//����Lambda���ʽ�������ش���������
	str.stream().filter(s->s.length()>=4).map(m->m.toUpperCase()).forEach(System.out::println);
	}
public static List<String> filter(List<String> str){//���˷��������س��ȴ��ڵ���4���ַ�������
		List<String> list=new ArrayList<String>();
		for(String s:str){
			if (s.length()>=4){
				list.add(s);
			}
		}
		return list;
	}
public static List<String> toUpper(List<String> str){//�ַ������������������������ַ���ת���ɴ�д�ַ�
		ArrayList<String> ulist=new ArrayList<String>();
		for(String s :str){
			ulist.add(s.toUpperCase());
		}
		return ulist;
	}
}
