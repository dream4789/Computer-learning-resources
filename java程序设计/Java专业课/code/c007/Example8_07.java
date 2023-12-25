import java.util.HashSet;
import java.util.TreeSet;

public class Example8_07 {

	public static void main(String[] args) {
		HashSet<String> race0 = new HashSet<String>();//创建第一个比赛名单
		HashSet<String> race1 = new HashSet<String>();//创建第二个比赛名单
		race0.add("wu");//向第一个名单中添加人员，共4人
		race0.add("wang");
		race0.add("li");
		race0.add("zhang");
		race1.add("zhao");//向第二个名单中添加人员，共4人
		race1.add("wang");
		race1.add("li");
		race1.add("liu");
		HashSet race = new HashSet(race0);
		race.addAll(race1);//将两个名单合并
		System.out.println("班级参赛人数为 "+race.size()+" 人");
		TreeSet list = new TreeSet(race);//将人员名单放入TreeSet集合对象，自动完成排序
		System.out.println("参赛人员: ");
		for (String s:list){//遍历输出人员名单
			System.out.println(s);
		}
	}

}
