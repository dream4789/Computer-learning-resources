import java.util.*;
public class Example8_05 {
public static void main(String[] args) {
		ArrayList<String> roster = new ArrayList<String>();//创建一个ArrayList数组
		roster.add("zhang");//将名字逐一加入数组
		roster.add("wang");
		roster.add("li");
		roster.add("zhao");
		System.out.print("roster =");//通过逐一获取名字，显示名单内容
		for (int i=0;i<roster.size();i++){
			System.out.print(roster.get(i)+" ");
		}
		System.out.println();
		System.out.println("roster ="+roster);//直接显示动态数组内容

		int number=1;
		for(int i=0;i<roster.size();i+=2){//在每个名字前面插入序号
			roster.add(i,String.valueOf(number));
			number++;
		}
		System.out.println("new roster ="+roster);//输出新的数组内容

		roster.remove(0);//删除第一个人的序号
		roster.remove(0);//删除第一个人的名字
		System.out.println("remove one person,roster ="+roster);//输出数组内容
	}
}
